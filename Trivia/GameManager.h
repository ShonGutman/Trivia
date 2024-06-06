#pragma once

#include<vector>
#include <mutex>
#include <algorithm>
#include "Game.h"
#include "IDatabase.h"
#include "Room.h"

class GameManager
{
public:

	/*
	* Function to get the singleton instance
	*
	* @return the instance of GameManager
	*/
	static GameManager& get(IDatabase* database = nullptr);

	// Delete copy constructor and assignment operator to prevent copies
	GameManager(const GameManager& other) = delete;
	GameManager& operator=(const GameManager& other) = delete;

	/*
	* Creates a new game based on the specified room and adds it to the GameManager's collection of games.
	*
	* @param room The room from which to create the game.
	* @return the Game that was created
	*/
	Game& createGame(const Room& room);

	Game& getGame(const unsigned int id);

	void deleteGame(const unsigned int id);


private:

	GameManager(IDatabase* database);

	IDatabase* _database;

	std::vector<Game> _games;
};
