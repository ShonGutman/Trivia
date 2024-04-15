#pragma once

#include <set>
#include <mutex>
#include "LoggedUser.h"
#include "IDatabase.h"
#include "RegexHelper.h"

using std::string;

class LoginManager
{
public:
	// CTOR //
	LoginManager() = default;
	LoginManager(IDatabase* database);

	/**
	 * Signs up a new user.
	 *
	 * This function registers a new user by checking if the username already exists
	 * in the database. If the username does not exist, the function proceeds to sign
	 * up the user with the provided username, password, and email.
	 *
	 * @param username The username of the new user.
	 * @param password The password of the new user.
	 * @param email The email address of the new user.
	 */
	void signup(const string& username, const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday);

	/**
	 * Logs in a user.
	 *
	 * This function logs in a user by verifying the provided username and password
	 * against the database. If the username and password match, a new LoggedUser object
	 * is created and added to the list of logged-in users.
	 *
	 * @param username The username of the user trying to log in.
	 * @param password The password of the user trying to log in.
	 */
	void login(const string& username, const string& password);

	/**
	 * Logs out a user.
	 *
	 * This function logs out a user by removing the corresponding LoggedUser object
	 * from the vector of logged-in users based on the provided username.
	 *
	 * @param username The username of the user to log out.
	 */
	void logout(const string& username);


private:

	/**
	 * Checks if the sign-up input is valid.
	 *
	 * This function checks if the provided sign-up input (password, email, address,
	 * phone number, and birthday) meets the required structure and format.
	 *
	 * @param password The password to be validated.
	 * @param email The email address to be validated.
	 * @param address The address to be validated.
	 * @param phoneNumber The phone number to be validated.
	 * @param birthday The birthday to be validated.
	 * @throws std::runtime_error if any of the input parameters does not match the required structure.
	 */
	static void isSignupInputValid(const string& password, const string& email, const string& address, const string& phoneNumber, const string& birthday);

	IDatabase* _database;
	std::set<LoggedUser> _loggedUsers;
};
