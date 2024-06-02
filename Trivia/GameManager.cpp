#include "GameManager.h"

//init num of games created to be zero at the start
int GameManager::_amountOfGamesCreated = 0;

GameManager& GameManager::get(IDatabase* database)
{
	static GameManager instance(database);
	return instance;
}

Game& GameManager::getGame(unsigned int gameID)
{
	for (auto& it : _games)
	{
		if (it.getGameID() == gameID)
		{
			return it;
		}
	}
	throw std::runtime_error("There is no game with given ID");
}

void GameManager::createGame(const Room& room)
{
	std::set<LoggedUser> usersInGame = room.getAllUsers();
	Game game = Game(_database->getQuestions(room.getRoomData().numOfQuestionsInGame),
		std::vector<LoggedUser>(usersInGame.begin(), usersInGame.end()),
			_amountOfGamesCreated);

	_games.push_back(game);
}

GameManager::GameManager(IDatabase* database)
	:_database(database), _games()
{
}
