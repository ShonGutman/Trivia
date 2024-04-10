#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase()
{
	open();
}

SqliteDatabase::~SqliteDatabase()
{
	close();
}

bool SqliteDatabase::open()
{
	string dbName = "myTrivia.sqlite";
	int doesExist = _access(dbName.c_str(), 0);

	//check if there is error in opening the DB
	if (sqlite3_open(dbName.c_str(), &_db) != SQLITE_OK)
	{
		_db = nullptr;
		throw ("Failed to open DB!");
		return false;
	}

	if (doesExist != 0)
	{
		//check if init tables failed
		if (!initTables())
		{
			_db = nullptr;
			return false;
		}
	}
	return true;
}

void SqliteDatabase::close()
{
	sqlite3_close(_db);
	_db = nullptr;
}

bool SqliteDatabase::create_users_table()
{
	const string sqlStatement = R"(CREATE TABLE users (
		id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
		username TEXT NOT NULL,
		password TEXT NOT NULL,
		email TEXT NOT NULL);)";

	return preformSqlRequest(sqlStatement);
}

bool SqliteDatabase::initTables()
{
	return create_users_table();
}

bool SqliteDatabase::preformSqlRequest(string sql, int(*callback)(void*, int, char**, char**), void* data)
{
	char* errorMsg = nullptr;
	if (sqlite3_exec(_db, sql.c_str(), callback, data, &errorMsg) != SQLITE_OK)
	{
		std::cerr << "error: " << errorMsg << std::endl;
		sqlite3_free(errorMsg);
		throw ("Failed to preform SQL!");
		return false;
	}
	sqlite3_free(errorMsg);
	return true;
}
