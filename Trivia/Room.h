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
	
	//CTOR
	RoomData(unsigned int id, std::string name, unsigned int maxPlayers, unsigned int numOfQuestions, unsigned int timePerQuestion, bool isActive = false)
	{
		this->id = id;
		this->name = name;
		this->maxPlayers = maxPlayers;
		this->numOfQuestionsInGame = numOfQuestions;
		this->timePerQuestion = timePerQuestion;
		this->isActive = isActive;
	}
};

class Room
{
public:

	//CTOR//
	Room(const RoomData& data, const LoggedUser& roomAdmin);

	/**
	 * Adds a user to the room.
	 *
	 * @param user The user to be added to the room.
	 * @throws std::runtime_error if the user is already logged in the room.
	 */
	void addUser(const LoggedUser& user);

	/**
	 * Removes a user from the room.
	 *
	 * @param user The user to be removed from the room.
	 * @throws std::runtime_error if the user does not exist in the room.
	 */
	void removeUser(const LoggedUser& user);


	/**
	 * Retrieves all users currently in the room.
	 *
	 * @return A set containing all logged users in the room.
	 */
	std::set<LoggedUser> getAllUsers() const;

	/**
	 * Retrieves the admin of the room
	 *
	 * @return room admin of the current room
	 */
	LoggedUser getRoomAdmin() const;

	/**
	 * Retrieves data about the room.
	 *
	 * @return Roomdata with all data to know about the room.
	 */
	const RoomData getRoomData() const;

	/**
	 * changes room to be active
	 */
	void makeRoomActive();

private:
	RoomData _metaData;
	std::set<LoggedUser> _users;
	LoggedUser _roomAdmin;
};
