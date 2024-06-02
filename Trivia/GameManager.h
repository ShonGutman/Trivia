#pragma once

#include<vector>
#include "Game.h"
#include "IDatabase.h"

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



private:

	GameManager(IDatabase* database);

	IDatabase* _database;

	std::vector<Game> _games;

	static int _amountOfGamesCreated;
};
