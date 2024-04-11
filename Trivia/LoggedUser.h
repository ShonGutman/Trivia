#pragma once

#include <iostream>

class LoggedUser
{
public:

	// CTOR //
	LoggedUser(const std::string& username);

	// get and set
	std::string getName() const;

	void setName(const std::string& username);

	/**
	 * Checks if this LoggedUser object is equal to another LoggedUser object.
	 *
	 * This function compares this LoggedUser object with another LoggedUser object
	 * to determine if they are equal based on their attributes.
	 *
	 * @param other The other LoggedUser object to compare with.
	 * @return true if the objects are equal, false otherwise.
	 */
	bool operator==(LoggedUser& other);

private:
	std::string _username;
};
