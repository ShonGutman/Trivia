#include "Room.h"
#include <mutex>

static std::mutex _loggedMutex;

Room::Room(const RoomData& data)
	:_metaData(data), _users()
{
}

void Room::addUser(const LoggedUser& user)
{
	//lock the mutex - to protect _users (shared variable)
	std::unique_lock<std::mutex> locker(_loggedMutex);
	auto result = _users.insert(user);
	locker.unlock();

	//result is a pair of 2 values a iterator to object and bool to indicate if element was inserted successfully
	if (!result.second)
	{
		throw std::runtime_error("User is already logged to room!");
	}
}

void Room::removeUser(const LoggedUser& user)
{
	//lock the mutex - to protect _users (shared variable)
	std::unique_lock<std::mutex> locker(_loggedMutex);
	bool erased = _users.erase(user);
	locker.unlock();

	if (!erased)
	{
		throw std::runtime_error("User doesn't exists in current room, can't erase ...");
	}
}

const std::set<LoggedUser>& Room::getAllUsers() const
{
	return _users;
}

const RoomData Room::getRoomData() const
{
	return _metaData;
}
