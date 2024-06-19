#pragma once

#include <sstream>
#include <io.h>
#include <vector>
#include "IDatabase.h"
#include "sqlite3.h"

#define DB_FILENAME "myTrivia.sqlite"

#define NUM_OF_INCORRECT 3
#define NUM_QUESTIONS 10

#define QUESTION_COL "question"
#define CORRECT_COL "correct"
#define INCORRECT1_COL "incorrect1"
#define INCORRECT2_COL "incorrect2"
#define INCORRECT3_COL "incorrect3"

#define USERNAME_COL "username"
#define RIGHT_ANS_COL "numOfRightAns"

class SqliteDatabase : public IDatabase
{
public:
	// CTOR && DTOR //
	SqliteDatabase();
	virtual ~SqliteDatabase();

	/**
	 * Checks if a user with the specified username exists in the SQLite database.
	 *
	 * This function queries the SQLite database to determine if a user with the
	 * specified username exists.
	 *
	 * @param username The username to check for existence in the database.
	 * @return true if the user exists, false otherwise.
	 */
	bool doesUserExists(const string& username) override;

	/**
	 * Checks if the password matches the one associated with the specified username in the SQLite database.
	 *
	 * This function queries the SQLite database to check if the password provided
	 * matches the password associated with the given username.
	 *
	 * @param username The username whose password is to be checked.
	 * @param password The password to compare with the one stored in the database.
	 * @return true if the password matches, false otherwise.
	 */
	bool doesPasswordMatch(const string& username, const string& password) override;

	/**
	 * Registers a new user in the SQLite database.
	 *
	 * This function inserts a new record into the SQLite database to register a new user
	 * with the provided username, password, and email.
	 *
	 * @param username The username of the new user.
	 * @param password The password of the new user.
	 * @param email The email address of the new user.
	 * @param address The address of the new user.
	 * @param phoneNumber The phone number of the new user.
	 * @param birthday The phone birthday of the new user.
	 */
	void signup(const string& username, const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday) override;

	/**
	 * Retrieves a vector of questions from the database.
	 *
	 * @param numOfQuestions The number of questions to retrieve. Defaults to NUM_QUESTIONS if not specified.
	 * @return A vector of Question objects retrieved from the database.
	 */
	std::vector<Question> getQuestions(const int numOfQuestions = NUM_QUESTIONS) override;

	/**
	* creates a new column in statistics table for user
	* 
	* @param user to create new column with 0 in values
	*/
	void createEmptyStatisticColumn(const string& username) override;

	/**
	* Retrieves the average answer time for a player.
	*
	* @param username The username of the player.
	* @return The average answer time of the player.
	*/
	float getPlayerAverageAnswerTime(const string& username) override;

	/**
	 * Retrieves the number of correct answers for a player.
	 *
	 * @param username The username of the player.
	 * @return The number of correct answers of the player.
	 */
	int getNumOfCorrectAnswers(const string& username) override;

	/**
	 * Retrieves the number of worng answers for a player.
	 *
	 * @param username The username of the player.
	 * @return The number of worng answers of the player.
	 */
	int getNumOfWrongAnswers(const string& username) override;

	/**
	 * Retrieves the total number of answers (correct and incorrect) for a player.
	 *
	 * @param username The username of the player.
	 * @return The total number of answers of the player.
	 */
	int getNumOfTotalAnswers(const string& username) override;

	/**
	 * Retrieves the number of games played by a player.
	 *
	 * @param username The username of the player.
	 * @return The number of games played by the player.
	 */
	int getNumOfPlayerGames(const string& username) override;

	/**
	 * Retrieves the score of a player.
	 *
	 * @param username The username of the player.
	 * @return The score of the player.
	 */
	int getPlayerScore(const string& username) override;

	/**
	 * Retrieves the highscores.
	 *
	 * @return A map containing username as string and their corresponding scores, representing the highscores.
	 */
	std::map<std::string, unsigned int> getHighscores() override;

	/*
	* Updates the statistics for each player based on the results of the game.
	* It calculates the new average answer time for each player and updates their statistics accordingly.
	*
	* @param Gameresults A vector containing the results of all players in the game.
	*/
	void updateStatistics(const std::vector<PlayerResults>& Gameresults) override;

	/*
	* adds a question to questions table based on the param
	* @param question the question
	* @param correct the correct ans
	* @param incorecct a string array holding 3 incorrect answers
	* @return true if inserted with no errors. false if there were errors
	*/
	bool addQuestion(const string& question, const string& correct, const string incorecct[NUM_OF_INCORRECT]);


private:

	/*
	*function opens SQL Database
	@return if Database was opened successfully
	*/
	bool open() override;

	/*
	* function closes Database
	*/
	void close() override;

	/*
	* function creates table of users inisde a given data base
	* @return true if table created succesfully. false if not
	*/
	bool create_users_table();

	/*
	* function creates table of stats inisde a given data base
	* @return true if table created succesfully. false if not
	*/
	bool create_statistics_table();

	/*
	* function creates table of questions inisde a given data base
	* @return true if table created succesfully. false if not
	*/
	bool create_questions_table();

	/*
	* adds 10 default questions to the question table
	* @return true if inserted with no errors. false if there were errors
	*/
	bool addQuestions();

	/*
	* function cinitalizes all tables in data base
	* @return true if all tables created succesfully. false if not
	*/
	bool initTables();

	/*
	* function preforms the sql request
	* @param sql - request from database
	* @param callback - function of callBack (optional)
	* @param data - data to callBack (optional)
	* @return if request was succesful
	*/
	bool preformSqlRequest(string sql, int(*callback)(void*, int, char**, char**) = nullptr, void* data = nullptr);

	//callBack functions:

	static int callbackNumber(void* data, int argc, char** argv, char** azColName);
	static int callbackQuestion(void* data, int argc, char** argv, char** azColName);
	static int callbackDouble(void* data, int argc, char** argv, char** azColName);
	static int callbackHighScoresMap(void* data, int argc, char** argv, char** azColName);


	/*
	* function preform string formating. given a string function will replace {} with value from args
	*
	* for exmp: format("hello, I am {}. I am {} years old", {"Shon", "17"})
	* result would be - "hello, I am Shon. I am 17 years old"
	*
	* ----------------------------------------------------------------------------------------
	* important: function assumes that amount of {} is exactly args.length()
	* the function will not check it!! it is the responsiblity of the programer!
	* ----------------------------------------------------------------------------------------
	*
	* @param fmt - string of format
	* @param args - vector of params to insert
	* @return formatted string
	*/
	static string format(string fmt, std::vector<string> args);

	/*
	* Calculates the total average based on the averages and number of games from two sources.
	* It computes the weighted average of the two averages using the number of games as weights.
	*
	* @param avg1 The average from the first source.
	* @param numGames1 The number of games from the first source.
	* @param avg2 The average from the second source.
	* @param numGames2 The number of games from the second source.
	* @return The total average calculated from both sources.
	*/
	double calculateTotalAverage(const double avg1, const unsigned int numGames1, const double avg2, const unsigned int numGames2);

	sqlite3* _db;
};
