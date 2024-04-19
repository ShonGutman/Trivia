#pragma once

#include <sstream>
#include <io.h>
#include <vector>
#include "IDatabase.h"
#include "sqlite3.h"

#define DB_FILENAME "myTrivia.sqlite"

#define NUM_OF_INCORRECT 3
#define NUM_QUESTIONS 10

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
	* adds a question to questions table based on the param
	* @param question the question
	* @param correct the correct ans
	* @param incorecct a string array holding 3 incorrect answers
	* @return true if inserted with no errors. false if there were errors
	*/
	bool addQuestion(string question, string correct, string incorecct[NUM_OF_INCORRECT]);

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



	sqlite3* _db;
};
