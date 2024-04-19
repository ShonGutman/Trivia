#pragma once

#include <string>
#include <iostream>

using std::string;

class IDatabase
{
public:

	virtual ~IDatabase() = default;

	virtual bool doesUserExists(const string& username) = 0;

	virtual bool doesPasswordMatch(const string& username, const string& password) = 0;

	virtual void signup(const string& username, const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday) = 0;

protected:

	virtual bool open() = 0;

	virtual void close() = 0;
};
