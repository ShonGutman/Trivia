#include "StatisticsManager.h"

StatisticsManager::StatisticsManager(IDatabase* database)
{
	_database = database;
}

StatisticsManager::~StatisticsManager()
{
	delete _database;
}

StatisticsManager& StatisticsManager::get(IDatabase* database)
{
	static StatisticsManager instance(database);
	return instance;
}

GetHighscoreResponse StatisticsManager::getHighScore()
{
	GetHighscoreResponse highScore;

	highScore.highScores = _database->getHighscores();

	return highScore;
}

GetPersonalStatsResponse StatisticsManager::getUserStatistics(std::string username)
{
	GetPersonalStatsResponse userStats;

	userStats.numberOfGames = _database->getNumOfPlayerGames(username);
	userStats.numRightAns = _database->getNumOfCorrectAnswers(username);
	userStats.numWrongAns = _database->getNumOfWrongAnswers(username);
	userStats.avgTimeForAns = _database->getPlayerAverageAnswerTime(username);

	return userStats;
}
