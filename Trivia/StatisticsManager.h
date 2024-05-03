#pragma once

#include <vector>
#include <map>
#include <iostream>
#include "Responses.h"
#include "SqliteDatabase.h"
#include "IDatabase.h"

class StatisticsManager : public IDatabase
{
	// CTOR && DTOR //
	StatisticsManager();
	virtual ~StatisticsManager();

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
	IDatabase* _database;
};