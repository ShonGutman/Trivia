#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
	_database = new SqliteDatabase();
}

StatisticsManager::~StatisticsManager()
{
	delete _database;
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
