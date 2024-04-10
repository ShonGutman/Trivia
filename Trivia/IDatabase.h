#pragma once

#include <string>
#include <iostream>

using std::string;

class IDatabase
{
public:

	virtual ~IDatabase() = default;

	virtual bool doesUserExists(const string& username) const = 0;

	virtual bool doesPasswordMatch(const string& username, const string& password) const = 0;

	virtual void signUp(const string& username, const string& password, const string& email) = 0;

protected:

	virtual bool open() = 0;

	virtual void close() = 0;
};
