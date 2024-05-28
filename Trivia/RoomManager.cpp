#include "RoomManager.h"

#define NUM_QUESTIONS 10

//init num of rooms joined to be zero at the start
int RoomManager::_amountOfRoomsEverJoined = 0;

RoomManager& RoomManager::get()
{
	static RoomManager instance;
	return instance;
}

void RoomManager::createRoom(const LoggedUser& roomAdmin, const RoomData& data)
{

	if (data.numOfQuestionsInGame > NUM_QUESTIONS)
	{ 
		throw std::runtime_error("Questions limit in game is: " + std::to_string(NUM_QUESTIONS));
	}

	//create new room
	auto result = _rooms.insert({ data.id, Room(data, roomAdmin) });

	//result is a pair of 2 values an iterator to object and bool to indicate if element was inserted successfully
	if (!result.second)
	{
		throw std::runtime_error("room with that ID already exists!");
	}

	RoomManager::_amountOfRoomsEverJoined++;
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

void RoomManager::removeUserFromAllRooms(const LoggedUser& user)
{
	std::vector<int> roomsToDelete;

	for (auto& pair : _rooms)
	{
		try
		{
			pair.second.removeUser(user);
		}
		catch (const std::exception&)
		{
			//if remove failed it means user isnt a member of room. no need to handle anything

			//check if user is the admi
			if (pair.second.getRoomAdmin() == user)
			{
				roomsToDelete.push_back(pair.first);
			}
		}

	}

	for (const auto& it : roomsToDelete)
	{
		//delete all rooms that relate to admin
		deleteRoom(it);
	}
}

const int RoomManager::getNextRoomId() const
{
	return RoomManager::_amountOfRoomsEverJoined + 1;
}
