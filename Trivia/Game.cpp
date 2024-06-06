#include "Game.h"

static std::mutex _playingPlayersMutex;

Game::Game(const std::vector<Question> questions, const std::vector<LoggedUser> users, const unsigned int GameID)
	:_questions(questions), _gameID(GameID), _numOfPlayersStillPlaying(users.size())
{
	for (size_t i = 0; i < _numOfPlayersStillPlaying; i++)
	{
		_players.push_back(PlayerGame(users[i]));
	}
}

Question Game::getNextQuestionForUser(const LoggedUser& user)
{
	for (auto& it : _players)
	{
		if (it.user == user && it.isStillPlaying)
		{
			//change the question to the player and increase the question ID
			if(it.NextQuestionID < _questions.size())
			{
				it.playerGameData.currentQuestion = _questions[it.NextQuestionID++];
				return it.playerGameData.currentQuestion;
			}
		}
	}

	throw std::runtime_error("Can't get question for user " + user.getName());

}

void Game::removePlayer(const LoggedUser& user)
{
	for (auto& it : _players)
	{
		if (it.user == user && it.isStillPlaying)
		{
			//make user not playing anymore
			it.isStillPlaying = false;

			//lock the mutex - to protect _numOfPlayersStillPlaying (shared var)
			std::lock_guard<std::mutex> locker(_playingPlayersMutex);
			//decrease amount of playing players
			_numOfPlayersStillPlaying--;

			return;
		}
	}

	throw std::runtime_error("User doesn't exist in game, can't remove him!");
}

unsigned int Game::submitAnswer(const LoggedUser& user, const unsigned int answerID, const double timeForQuestion)
{

	for (auto& it : _players)
	{
		if (it.user == user && it.isStillPlaying)
		{
			bool isRight = it.playerGameData.currentQuestion.getCorrectAnserID() == answerID;

			//add time it took to answer to avg
			it.playerGameData.avgTimeForAns = addToAvg(it.playerGameData.avgTimeForAns,
				it.playerGameData.numRightAns + it.playerGameData.numWrongAns, timeForQuestion);

			//check if player was right or wrong
			if (isRight)
			{
				it.playerGameData.numRightAns++;
			}

			else
			{
				it.playerGameData.numWrongAns++;
			}

			return it.playerGameData.currentQuestion.getCorrectAnserID();
		}
	}
		throw std::runtime_error("User isn't playing. can't submit answer");
}

unsigned int Game::FinishedGame(const LoggedUser& user)
{
	for (auto& it : _players)
	{
		if (it.user == user && it.isStillPlaying)
		{
			//check if player reached the limit of questions
			if (it.NextQuestionID == _questions.size())
			{
				it.isStillPlaying = false;

				//lock the mutex - to protect _numOfPlayersStillPlaying (shared var)
				std::lock_guard<std::mutex> locker(_playingPlayersMutex);
				return --_numOfPlayersStillPlaying;
			}
		}
	}
}

unsigned int Game::getGameID() const
{
	return _gameID;
}

bool Game::isFinished() const
{
	//lock the mutex - to protect _numOfPlayersStillPlaying (shared var)
	std::lock_guard<std::mutex> locker(_playingPlayersMutex);
	return 0 == _numOfPlayersStillPlaying;
}

std::vector<PlayerResults> Game::getGameResults() const
{
	std::vector<PlayerResults> results;

	for (auto& it : _players)
	{
		results.push_back((PlayerResults)it);
	}

	return results;
}

double Game::addToAvg(const double avg, const unsigned int size, const double addedValue)
{
	return (avg * size + addedValue) / (size + 1);
}
