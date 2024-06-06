#include "GameManager.h"

static std::mutex _gamesMutex;

GameManager& GameManager::get(IDatabase* database)
{
	static GameManager instance(database);
	return instance;
}

Game& GameManager::createGame(const Room& room)
{
	std::set<LoggedUser> usersInGame = room.getAllUsers();
	Game game = Game(_database->getQuestions(room.getRoomData().numOfQuestionsInGame),
		std::vector<LoggedUser>(usersInGame.begin(), usersInGame.end()),
			room.getRoomData().id);

	//lock the mutex - to protect _gamesMutex (shared var)
	std::lock_guard<std::mutex> locker(_gamesMutex);
	_games.push_back(game);
	return _games.back();
}

Game& GameManager::getGame(const unsigned int id)
{
	//lock the mutex - to protect _gamesMutex (shared var)
	std::lock_guard<std::mutex> locker(_gamesMutex);
	for (auto& game : _games)
	{
		if (game.getGameID() == id)
		{
			return game;
		}
	}
}

void GameManager::deleteGame(const unsigned int id)
{
	//lock the mutex - to protect _gamesMutex (shared var)
	std::lock_guard<std::mutex> locker(_gamesMutex);

	auto it = std::find_if(_games.begin(), _games.end(),
		[id](const Game& game) {return game.getGameID() == id; });

	if (it != _games.end())
	{
		submitResultsToDB(*it);
		_games.erase(it);
	}

}

void GameManager::submitResultsToDB(const Game& game) const
{
	_database->updateStatistics(game.getGameResults());
}

GameManager::GameManager(IDatabase* database)
	:_database(database), _games()
{
}
