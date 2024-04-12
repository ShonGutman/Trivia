#pragma once

#include <iostream>

class LoggedUser
{
public:

	// CTOR //
	LoggedUser(const std::string& username);

	// get and set //
	std::string getName() const;

	void setName(const std::string& username);

	//add operator overloading of <, <=, ==, !=, >=, and > to support std::set

	bool operator<(const LoggedUser& other) const;

	bool operator<=(const LoggedUser& other) const;

	bool operator==(const LoggedUser& other) const;

	bool operator!=(const LoggedUser& other) const;

	bool operator>=(const LoggedUser& other) const;

	bool operator>(const LoggedUser& other) const;

private:
	std::string _username;
};
