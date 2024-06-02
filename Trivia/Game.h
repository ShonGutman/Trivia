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

	GameData() = default;

	GameData(Question question)
	{
		currentQuestion = question;
	}

};

struct playerGame
{
	LoggedUser user;
	GameData playerGameData;
	unsigned int currentQuestionID = 0;
	bool isStillPlaying = true;

	playerGame(LoggedUser user, Question question)
	{
		user = user;
		playerGameData = GameData(question);
	}
};

class Game
{
public:

	//CTOR of class Game //
	Game(const std::vector<Question> questions, const std::vector<LoggedUser> users, const unsigned int GameID);

	/*
	* Retrieves the next question for the specified user, updating their game status accordingly.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it increments the user's current question ID and checks if they have reached the question limit.
	* If the user has reached the limit, they are marked as no longer playing. If not, the next question is assigned
	* to the user and returned. If the user is not found or is not playing, an exception is thrown.
	*
	* @param user The logged-in user requesting the next question.
	* @return The next question assigned to the user.
	* @throws std::runtime_error If the user is not found or is not playing.
	*/
	Question getNextQuestionForUser(const LoggedUser& user);

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
	* Submits an answer for the specified user, updates their game data, and progresses to the next question if applicable.
	* It iterates through the players map to find the user and checks if they are still playing.
	* If found, it verifies if the submitted answer is correct, updates the average time for answering questions,
	* and increments the count of right or wrong answers accordingly.
	* If the user is not found or is not playing, an exception is thrown.
	*
	* @param user The logged-in user submitting the answer.
	* @param answerID The ID of the answer submitted by the user.
	* @param timeForQuestion The time taken by the user to answer the question.
	* @throws std::runtime_error If the user is not found or is not playing.
	*/
	void submitAnswer(const LoggedUser& user, const unsigned int answerID, const double timeForQuestion);

	/*
	* Retrieves the ID of the game.
	*
	* @return The ID of the game.
	*/
	unsigned int getGameID() const;


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