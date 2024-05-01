#pragma once

#include <vector>
#include<iostream>
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
	 * @return A vector of strings representing the high scores.
	 */
	std::vector<std::string> getHighScore();

	/**
	 * Retrieves the statistics for a specific user.
	 *
	 * @param username The username for which statistics are to be retrieved.
	 * @return A vector of strings representing the user statistics.
	 */
	std::vector<std::string> getUserStatistics(std::string username);


private:
	IDatabase* _database;
};