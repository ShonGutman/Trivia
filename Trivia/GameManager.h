#pragma once

#include<vector>
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
	* Retrieves the game with the specified ID.
	*
	* @param gameID The ID of the game to retrieve.
	* @return Reference to the game object with the specified ID.
	* @throws std::runtime_error If no game with the given ID is found.
	*/
	Game& getGame(unsigned int gameID);

	/*
	* Creates a new game based on the specified room and adds it to the GameManager's collection of games.
	*
	* @param room The room from which to create the game.
	*/
	void createGame(const Room& room);


private:

	GameManager(IDatabase* database);

	IDatabase* _database;

	std::vector<Game> _games;

	static int _amountOfGamesCreated;
};
