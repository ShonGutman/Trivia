#pragma once

#include <vector>
#include <map>
#include <iostream>
#include "Responses.h"
#include "SqliteDatabase.h"
#include "IDatabase.h"

class StatisticsManager
{
	// DTOR //
	~StatisticsManager();

	/*
	* Function to get the singleton instance
	*
	* @param database the database needed, not a must
	* @return the instance of StatisticsManager
	*/
	static StatisticsManager& get(IDatabase* database = nullptr);

	// Delete copy constructor and assignment operator to prevent copies
	StatisticsManager(const StatisticsManager&) = delete;
	StatisticsManager& operator=(const StatisticsManager&) = delete;

	/**
	 * Retrieves the high scores from the system.
	 *
	 * @return A GetHighscoreResponse that has map and status
	 * first - name of user, sec - score;
	 */
	GetHighscoreResponse getHighScore();

	/**
	 * Retrieves the statistics for a specific user.
	 *
	 * @param username The username for which statistics are to be retrieved.
	 * @return GetPersonalStatsResponse struct
	 */
	GetPersonalStatsResponse getUserStatistics(std::string username);


private:

	// CTOR //
	StatisticsManager(IDatabase* database);

	IDatabase* _database;
};