#pragma once

#include <sstream>
#include <io.h>
#include "IDatabase.h"
#include "sqlite3.h"

class SqliteDatabase : public IDatabase
{
public:
	// CTOR && DTOR //
	SqliteDatabase();
	virtual ~SqliteDatabase();

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


	sqlite3* _db;
};
