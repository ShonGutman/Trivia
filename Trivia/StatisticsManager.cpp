#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
	_database = new SqliteDatabase();
}

StatisticsManager::~StatisticsManager()
{
	delete _database;
}
