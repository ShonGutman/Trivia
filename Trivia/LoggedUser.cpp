#include "LoggedUser.h"

#define NOT_LOGGED_USERNAME ""

LoggedUser::LoggedUser()
	:_username(NOT_LOGGED_USERNAME)
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

bool LoggedUser::isLogged() const
{
	return _username != NOT_LOGGED_USERNAME;
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
