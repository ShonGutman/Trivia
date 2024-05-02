#include "RoomManager.h"

//init num of rooms joined to be zero at the start
int RoomManager::_amountOfRoomsEverJoined = 0;

RoomManager& RoomManager::get()
{
	static RoomManager instance;
	return instance;
}

void RoomManager::createRoom(const LoggedUser auther, const RoomData data)
{
	//create new room
	auto result = _rooms.insert({ data.id, Room(data) });

	//result is a pair of 2 values an iterator to object and bool to indicate if element was inserted successfully
	if (!result.second)
	{
		throw std::runtime_error("room with that ID already exists!");
	}

	RoomManager::_amountOfRoomsEverJoined++;

	//add auther to the room
	_rooms.at(data.id).addUser(auther);
}

void RoomManager::deleteRoom(const unsigned int roomID)
{
	bool erased = _rooms.erase(roomID);

	if (!erased)
	{
		throw std::runtime_error("room doesn't exist, can't erase ...");
	}
}

bool RoomManager::getRoomState(const unsigned int roomID) const
{
	return _rooms.at(roomID).getRoomData().isActive;
}

std::vector<RoomData> RoomManager::getRooms() const
{
	std::vector<RoomData> roomsData;

	for (auto& it : _rooms)
	{
		roomsData.push_back(it.second.getRoomData());
	}
	return roomsData;
}

Room& RoomManager::getRoom(const unsigned int roomID)
{
	return _rooms.at(roomID);
}

const int RoomManager::getNextRoomId() const
{
	return RoomManager::_amountOfRoomsEverJoined + 1;
}
