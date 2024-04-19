#include "Room.h"

Room::Room(const RoomData& data)
	:_metaData(data), _users()
{
}

const std::set<LoggedUser>& Room::getAllUsers() const
{
	return _users;
}
