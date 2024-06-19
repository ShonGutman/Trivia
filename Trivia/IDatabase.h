#pragma once

#include <string>
#include <iostream>
#include <list>
#include <map>
#include "Question.h"
#include "PlayerResults.h"

#define NUM_OF_INCORRECT 3

using std::string;

class IDatabase
{
public:

	virtual ~IDatabase() = default;

	virtual bool doesUserExists(const string& username) = 0;

	virtual bool doesPasswordMatch(const string& username, const string& password) = 0;

	virtual void signup(const string& username, const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday) = 0;

	virtual std::vector<Question> getQuestions(const int numOfQuestions) = 0;

	virtual void createEmptyStatisticColumn(const string& username) = 0;

	virtual float getPlayerAverageAnswerTime(const string& username) = 0;

	virtual int  getNumOfCorrectAnswers(const string& username) = 0;

	virtual int  getNumOfWrongAnswers(const string& username) = 0;

	virtual int  getNumOfTotalAnswers(const string& username) = 0;

	virtual int  getNumOfPlayerGames(const string& username) = 0;

	virtual int  getPlayerScore(const string& username) = 0;

	virtual std::map<std::string, unsigned int> getHighscores() = 0;

	virtual void updateStatistics(const std::vector<PlayerResults>& Gameresults) = 0;

	virtual bool addQuestion(const string& question, const string& correct, const string incorecct[NUM_OF_INCORRECT]) = 0;

protected:

	virtual bool open() = 0;

	virtual void close() = 0;
};
