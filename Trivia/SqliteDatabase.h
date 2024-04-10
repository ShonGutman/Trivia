#pragma once

#include <sstream>
#include <io.h>
#include <vector>
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDatabase : public IDatabase
{
public:
	// CTOR && DTOR //
	SqliteDatabase();
	virtual ~SqliteDatabase();

	bool doesUserExists(const string& username) override;

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
	* @param db - given data base
	* @return true if table created succesfully. false if not
	*/
	bool create_users_table();

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
