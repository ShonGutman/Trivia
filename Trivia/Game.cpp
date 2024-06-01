#include "Game.h"

Question Game::getQuestionForUser(const LoggedUser& user) const
{
    return _players.at(user).currentQuestion;
}

void Game::removePlayer(const LoggedUser& user)
{
	bool erased = _players.erase(user);

	if (!erased)
	{
		throw std::runtime_error("User doesn't exist in game, can't erase ...");
	}
}
