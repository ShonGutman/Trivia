#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database)
	:_loggedUsers(), _database(database)
{
}

void LoginManager::signUp(const string& username, const string& password, const string& email)
{
	if (!_database->doesUserExists(username))
	{
		_database->signUp(username, password, email);
	}
}

void LoginManager::login(const string& username, const string& password)
{
	if (_database->doesPasswordMatch(username, password))
	{
		_loggedUsers.insert(LoggedUser(username));
	}
}

void LoginManager::logout(const string& username)
{
	_loggedUsers.erase(LoggedUser(username));
}


