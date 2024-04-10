#include "SqliteDatabase.h"

SqliteDatabase::SqliteDatabase()
{
	open();
}

SqliteDatabase::~SqliteDatabase()
{
	close();
}

bool SqliteDatabase::doesUserExists(const string& username) 
{
	string sqlStatement = R"(select count(*) from users where username = "{}";)";
	sqlStatement = format(sqlStatement, { username });

	int count = 0;
	preformSqlRequest(sqlStatement, callbackNumber, &count);

	return count != 0;
}

bool SqliteDatabase::doesPasswordMatch(const string& username, const string& password)
{
	string sqlStatement = R"(select count(*) from users where username = "{}" and
								password = "{}";)";
	sqlStatement = format(sqlStatement, { username, password });

	int count = 0;
	preformSqlRequest(sqlStatement, callbackNumber, &count);

	return count != 0;
}

void SqliteDatabase::signUp(const string& username, const string& password, const string& email)
{
	string sqlStatement = R"(insert into users values ("{}", "{}", "{}");)";
	sqlStatement = format(sqlStatement, { username, password, email });

	preformSqlRequest(sqlStatement);
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
		username TEXT PRIMARY KEY NOT NULL,
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

int SqliteDatabase::callbackNumber(void* data, int argc, char** argv, char** azColName)
{
	int* count = static_cast<int*>(data);

	if (argv[0] == NULL)
	{
		*count = 0;
		return 0;
	}

	*count = atoi(argv[0]);

	return 0;
}

string SqliteDatabase::format(string fmt, std::vector<string> args)
{
	std::stringstream ss;
	int i = fmt.find("{}");
	for (i; i != string::npos; i = fmt.find("{}"))
	{
		ss << fmt.substr(0, i);
		ss << args[0];
		//remove first value
		args.erase(args.begin());
		fmt = fmt.substr(i + 2);
	}
	ss << fmt;
	return ss.str();
}
