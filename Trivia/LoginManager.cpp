#include "LoginManager.h"

using re = RegexHelper;

static std::mutex _signupMutex;
static std::mutex _loggedMutex;

LoginManager::LoginManager(IDatabase* database)
	:_loggedUsers(), _database(database)
{
}

void LoginManager::signup(const string& username, const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday)
{
	isSignupInputValid(password, email, address, phoneNumber, birthday);

	//lock the mutex - to protect database (shared variable)
	std::unique_lock<std::mutex> locker(_signupMutex);
	if (!_database->doesUserExists(username))
	{
		_database->signup(username, password, email, address, phoneNumber, birthday);
		locker.unlock();

		//lock the mutex - to protect _loggedUsers (shared variable)
		std::lock_guard<std::mutex> lock(_loggedMutex);
		//add user to logged users
		_loggedUsers.insert(LoggedUser(username));
	}

	else
	{
		throw std::runtime_error("User already exists, can't signup!");
	}
}

void LoginManager::login(const string& username, const string& password)
{
	if (!re::isPasswordLegal(password))
	{
		throw std::runtime_error("Password doesn't match required structure!");
	}

	if (_database->doesPasswordMatch(username, password))
	{
		//lock the mutex - to protect _loggedUsers (shared variable)
		std::unique_lock<std::mutex> locker(_loggedMutex);
		auto result = _loggedUsers.insert(LoggedUser(username));
		locker.unlock();

		//result is a pair of 2 values a iterator to object and bool to indicate if element was inserted successfully
		if (!result.second)
		{
			throw std::runtime_error("User is already logged!");
		}
	}

	else
	{
		throw std::runtime_error("password doesn't match given username!");
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
		throw std::runtime_error("User doesn't exists, can't erase ...");
	}
}

void LoginManager::isSignupInputValid(const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday)
{
	if (!re::isPasswordLegal(password))
	{
		throw std::runtime_error("Password doesn't match required structure!");
	}

	else if(!re::isEmailLegal(email))
	{
		throw std::runtime_error("Email doesn't match required structure!");
	}

	else if (!re::isAddressLegal(address))
	{
		throw std::runtime_error("Address doesn't match required structure!");
	}

	else if (!re::isPhoneNumberLegal(phoneNumber))
	{
		throw std::runtime_error("Phone number doesn't match required structure!");
	}

	else if (!re::isBirthdayLegal(birthday))
	{
		throw std::runtime_error("Birthday doesn't match required structure!");
	}
}


