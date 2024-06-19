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

	/*
	* Function to get the singleton instance
	* 
	* @param database the database needed, not a must
	* @return the instance of LoginManager
	*/
	static LoginManager& get(IDatabase* database = nullptr);

	// Delete copy constructor and assignment operator to prevent copies
	LoginManager(const LoginManager&) = delete;
	LoginManager& operator=(const LoginManager&) = delete;

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
	 * @param address The address of the new user.
	 * @param phoneNumber The phone number of the new user.
	 * @param birthday The phone birthday of the new user.
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

	/**
	 * Changes the password of an existing user.
	 *
	 * This function changes the password for a user by verifying the current password
	 * and then updating it with the new password if the current password is correct.
	 *
	 * @param username The username of the user.
	 * @param currentPassword The current password of the user.
	 * @param newPassword The new password to be set.
	 */
	void changePassword(const string& username, const string& currentPassword, const string& newPassword);


private:
	// Private constructor to prevent external instantiation
	// CTOR //
	LoginManager(IDatabase* database);

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
