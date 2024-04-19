#include "RoomManager.h"

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
