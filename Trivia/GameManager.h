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
	* It retrieves the users from the room and initializes a new game with the room's questions and ID.
	* The operation is protected by a mutex to ensure thread safety while modifying the shared games collection.
	*
	* @param room The room from which to create the game.
	* @return A reference to the newly created game.
	*/
	Game& createGame(const Room& room);

	/*
	* Retrieves the game with the specified ID.
	* This operation is protected by a mutex to ensure thread safety while accessing the shared games collection.
	* It iterates through the games and returns a reference to the game with the matching ID.
	*
	* @param id The ID of the game to retrieve.
	* @return A reference to the game object with the specified ID.
	* @throws std::runtime_error If no game with the given ID is found.
	*/
	Game& getGame(const unsigned int id);

	/*
	* Deletes the game with the specified ID from the GameManager's collection of games.
	* This operation is protected by a mutex to ensure thread safety while modifying the shared games collection.
	* It searches for the game with the given ID, submits its results to the database, and removes it from the collection.
	*
	* @param id The ID of the game to be deleted.
	*/
	void deleteGame(const unsigned int id);


private:

	/*
	* Submits the results of the game to the database for updating statistics.
	* It retrieves the game results and passes them to the database for updating player statistics.
	*
	* @param game The game whose results are to be submitted to the database.
	*/
	void submitResultsToDB(const Game& game) const;

	GameManager(IDatabase* database);

	IDatabase* _database;

	std::vector<Game> _games;
};
