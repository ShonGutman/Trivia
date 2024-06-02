#pragma once

#include <vector>
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

struct playerGame
{
	LoggedUser user;
	GameData playerGameData;
	unsigned int currentQuestionID = 0;
	bool isStillPlaying = true;
};

class Game
{
public:

	/*
	* Retrieves the current question for the specified user if the user is still playing.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it returns the current question assigned to the user.
	*
	* @param user The logged-in user for whom the question is to be retrieved.
	* @return The current question assigned to the user.
	* @throws std::runtime_error If the user is not found in the players map or is not still playing.
	*/
	Question getQuestionForUser(const LoggedUser& user) const;

	/*
	* Removes the specified user from the game by marking them as no longer playing.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it updates their status to not playing and decreases the count of players still playing.
	* If the user does not exist or is not found, an exception is thrown.
	*
	* @param user The logged-in user to be removed from the game.
	* @throws std::runtime_error If the user does not exist in the game or is not found.
	*/
	void removePlayer(const LoggedUser& user);

	/*
	* Submits an answer for the specified user, updates their game data, and progresses to the next question.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it verifies if the submitted answer is correct, updates the average time for answering questions,
	* and increments the count of right or wrong answers accordingly. It then either progresses to the next question
	* or marks the user as no longer playing if they have reached the question limit.
	* If the user is not found or is not playing, an exception is thrown.
	*
	* @param user The logged-in user submitting the answer.
	* @param answerID The ID of the answer submitted by the user.
	* @param timeForQuestion The time taken by the user to answer the question.
	* @throws std::runtime_error If the user is not found or is not playing.
	*/
	void submitAnswer(const LoggedUser& user, const unsigned int answerID, const double timeForQuestion);


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
	std::vector<playerGame> _players;
	unsigned int _gameID;
	unsigned int _numOfPlayersStillPlaying;
};