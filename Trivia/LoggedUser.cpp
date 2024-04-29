#include "LoggedUser.h"

#define NONE_INITIALIZED_USERNAME ""

LoggedUser::LoggedUser()
	:_username(NONE_INITIALIZED_USERNAME)
{
}

LoggedUser::LoggedUser(const std::string& username)
	:_username(username)
{
}

std::string LoggedUser::getName() const
{
	return _username;
}

void LoggedUser::setName(const std::string& username)
{
	_username = username;
}

void LoggedUser::setToInitialized()
{
	_username = NONE_INITIALIZED_USERNAME;
}

bool LoggedUser::isInitialized() const
{
	return _username != NONE_INITIALIZED_USERNAME;
}

bool LoggedUser::operator<(const LoggedUser& other) const
{
	return _username < other._username;
}

bool LoggedUser::operator<=(const LoggedUser& other) const
{
	return _username <= other._username;
}

bool LoggedUser::operator==(const LoggedUser& other) const
{
	return _username == other._username;
}

bool LoggedUser::operator!=(const LoggedUser& other) const
{
	return _username != other._username;
}

bool LoggedUser::operator>=(const LoggedUser& other) const
{
	return _username >= other._username;
}

bool LoggedUser::operator>(const LoggedUser& other) const
{
	return _username >= other._username;
}
