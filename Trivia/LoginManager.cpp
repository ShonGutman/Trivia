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
		_loggedUsers.push_back(LoggedUser(username));
	}
}

void LoginManager::logout(const string& username)
{
    for (auto it = _loggedUsers.begin(); it != _loggedUsers.end(); it++)
    {
        if (it->getName() == username)
        {
            _loggedUsers.erase(it);
			//we found the user, we can break out off the loop
			break;
        }
    }
}


