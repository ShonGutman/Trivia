#pragma once

#include <iostream>
#include <set>
#include "LoggedUser.h"

struct RoomData
{
	unsigned int id;
	std::string name;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
	bool isActive;
};

class Room
{
public:

	//CTOR//
	Room(const RoomData& data);

	void addUser(const LoggedUser& user);

	void removeUser(const LoggedUser& user);

	/**
	 * Retrieves all users currently in the room.
	 *
	 * @return A constant reference to a set containing all logged users in the room.
	 */
	const std::set<LoggedUser>& getAllUsers() const;

private:
	RoomData _metaData;
	std::set<LoggedUser> _users;
};
