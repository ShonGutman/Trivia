#include "GameManager.h"

GameManager& GameManager::get(IDatabase* database)
{
	static GameManager instance(database);
	return instance;
}

GameManager::GameManager(IDatabase* database)
	:_database(database), _games()
{
}
