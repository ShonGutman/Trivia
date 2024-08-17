#pragma once

#include <iostream>

class LoggedUser
{
public:

	// CTOR //
	LoggedUser();
	LoggedUser(const std::string& username);


	/**
	 * Gets the name of the LoggedUser.
	 *
	 * This function returns the username associated with the LoggedUser object.
	 *
	 * @return The username of the LoggedUser.
	 */
	std::string getName() const;

	/**
	 * Sets the name of the LoggedUser.
	 *
	 * This function sets the username associated with the LoggedUser object.
	 *
	 * @param username The username to set.
	 */
	void setName(const std::string& username);

	/**
	 * Sets user to be not initialized
	 */
	void setToNoneInitialized();

	/**
	 * Checks if user is initialized (username is not NONE_INITIALIZED_USERNAME)
	 *
	 * return: true if initialized false if not
	 */
	bool isInitialized() const;

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
