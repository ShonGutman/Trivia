#include "LoggedUser.h"

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
