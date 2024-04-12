#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* database)
	:_loggedUsers(), _database(database)
{
}

void LoginManager::signUp(const string& username, const string& password, const string& email)
{
	//lock the mutex - to protect database (shared variable)
	std::unique_lock<std::mutex> locker(_signupMutex);
	if (!_database->doesUserExists(username))
	{
		_database->signUp(username, password, email);
		locker.unlock();
	}

	else
	{
		throw("User already exists, can't signup!");
	}
}

void LoginManager::login(const string& username, const string& password)
{
	if (_database->doesPasswordMatch(username, password))
	{
		//lock the mutex - to protect _loggedUsers (shared variable)
		std::unique_lock<std::mutex> locker(_loggedMutex);
		auto result = _loggedUsers.insert(LoggedUser(username));
		locker.unlock();

		//result is a pair of 2 values a iterator to object and bool to indicate if element was inserted successfully
		if (!result.second)
		{
			throw("User is already logged!");
		}
	}

	else
	{
		throw("password doesn't match given username!");
	}
}

void LoginManager::logout(const string& username)
{
	//lock the mutex - to protect _loggedUsers (shared variable)
	std::unique_lock<std::mutex> locker(_loggedMutex);
	bool erased = _loggedUsers.erase(LoggedUser(username));
	locker.unlock();

	if (!erased)
	{
		throw("User doesn't exists, can't erase ...");
	}
}


