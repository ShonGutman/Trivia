#include "GameManager.h"

//init num of games created to be zero at the start
int GameManager::_amountOfGamesCreated = 0;

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
			_amountOfGamesCreated++);

	_games.push_back(game);
	return _games.back();
}

GameManager::GameManager(IDatabase* database)
	:_database(database), _games()
{
}
