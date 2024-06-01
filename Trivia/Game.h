#pragma once

#include <set>
#include <map>
#include "Question.h"
#include "LoggedUser.h"

struct GameData
{
	Question currentQuestion;
	unsigned int numRightAns = 0;
	unsigned int numWrongAns = 0;
	double avgTimeForAns = 0;
};

class Game
{
public:

	/*
	* Retrieves the current question for the specified user. It looks up the user in the
	* players map and returns their current question.
	*
	* @param user The logged-in user for whom the question is to be retrieved.
	* @return The current question assigned to the user.
	* @throws std::out_of_range If the user is not found in the players map.
	*/
	Question getQuestionForUser(const LoggedUser& user) const;

	/*
	* Removes the specified user from the game. It attempts to erase the user from the
	* players map. If the user does not exist in the game, an exception is thrown.
	*
	* @param user The logged-in user to be removed from the game.
	* @throws std::runtime_error If the user does not exist in the game.
	*/
	void removePlayer(const LoggedUser& user);


private:

	std::set<Question> _questions;
	std::map<LoggedUser, GameData> _players;
	unsigned int gameID;
};