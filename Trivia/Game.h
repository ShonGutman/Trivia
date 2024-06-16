#pragma once

#include <vector>
#include <map>
#include <mutex>
#include "Question.h"
#include "LoggedUser.h"
#include "PlayerResults.h"

struct GameData
{
	Question currentQuestion;
	unsigned int numRightAns = 0;
	unsigned int numWrongAns = 0;
	double avgTimeForAns = 0;

	GameData() = default;

	GameData(Question question)
	{
		currentQuestion = question;
	}

};

struct PlayerGame
{
	LoggedUser user;
	GameData playerGameData;
	unsigned int NextQuestionID = 0;
	bool isStillPlaying = true;

	PlayerGame(LoggedUser user)
	{
		this->user = user;
		playerGameData = GameData();
	}

	operator PlayerResults() const
	{
		return PlayerResults(user.getName(), this->playerGameData.numRightAns,
			this->playerGameData.numWrongAns, this->playerGameData.avgTimeForAns);
	}
};

class Game
{
public:

	//CTOR of class Game //
	Game(const std::vector<Question>& questions, const std::vector<LoggedUser>& users, const unsigned int GameID);


	/*
	* Retrieves the next question for the specified user if they are still playing and have not reached the end of the questions.
	* It iterates through the players to find the user, verifies they are still playing, and assigns the next question to them.
	* If the user has no more questions or is not found, an exception is thrown.
	*
	* @param user The logged-in user requesting the next question.
	* @return The next question assigned to the user.
	* @throws std::runtime_error If the user is not found, is not playing, or has no more questions.
	*/
	Question getNextQuestionForUser(const LoggedUser& user);

	/*
	* Removes the specified user from the game by marking them as no longer playing.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it updates their status to not playing and decreases the count of players still playing.
	* This operation is protected by a mutex to ensure thread safety.
	* If the user does not exist or is not found, an exception is thrown.
	*
	* @param user The logged-in user to be removed from the game.
	* @throws std::runtime_error If the user does not exist in the game or is not found.
	*/
	void removePlayer(const LoggedUser& user);

	/*
	* Submits an answer for the specified user, updates their game data, and progresses to the next question if applicable.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it verifies if the submitted answer is correct, updates the average time for answering questions,
	* and increments the count of right or wrong answers accordingly.
	* If the user is not found or is not playing, an exception is thrown.
	*
	* @param user The logged-in user submitting the answer.
	* @param answerID The ID of the answer submitted by the user.
	* @param timeForQuestion The time taken by the user to answer the question.
	* @return the id of the correct answer
	* @throws std::runtime_error If the user is not found or is not playing.
	*/
	unsigned int submitAnswer(const LoggedUser& user, const unsigned int answerID, const double timeForQuestion);

	/*
	* Marks the specified user as having finished the game if they have answered all questions.
	* It iterates through the players to find the user and checks if they are still playing.
	* If the user has answered all questions, they are marked as not playing, and the count of players still playing is decremented.
	* This operation is protected by a mutex to ensure thread safety.
	*
	* @param user The logged-in user to be marked as finished.
	* @return The updated number of players still playing.
	* @throws std::runtime_error If the user does not exist or is not found.
	*/
	unsigned int FinishedGame(const LoggedUser& user);

	/*
	* Retrieves the ID of the game.
	*
	* @return The ID of the game.
	*/
	unsigned int getGameID() const;

	/*
	* Checks if the game has finished by verifying if there are no players still playing.
	* This operation is protected by a mutex to ensure thread safety while accessing the shared variable.
	*
	* @return True if no players are still playing, otherwise false.
	*/
	bool isFinished() const;

	/*
	* Retrieves the results of the game for all players.
	* It iterates through the players and collects their results into a vector.
	*
	* @return A vector containing the results of all players in the game.
	*/
	std::vector<PlayerResults> getGameResults() const;


private:

	/*
	* Calculates the new average after adding a new value to a set of existing values.
	*
	* @param avg The current average of the existing values.
	* @param size The number of existing values.
	* @param addedValue The new value to be added to the set.
	* @return The new average after adding the new value.
	*/
	double addToAvg(const double avg, const unsigned int size, const double addedValue);

	std::vector<Question> _questions;
	std::vector<PlayerGame> _players;
	unsigned int _gameID;
	unsigned int _numOfPlayersStillPlaying;
};