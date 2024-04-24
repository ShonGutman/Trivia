#include "StatisticsManager.h"

StatisticsManager::StatisticsManager()
{
	_sqlDatabase = new SqliteDatabase();
}

StatisticsManager::~StatisticsManager()
{
	delete _sqlDatabase;
}
