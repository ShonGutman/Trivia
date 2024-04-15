#pragma once

#include <iostream>
#include <regex>

class RegexHelper
{
public:

	/**
	 * Checks if a password meets the specified criteria.
	 *
	 * This function checks if a password meets the following criteria:
	 * - Contains at least one number
	 * - Contains at least one lowercase letter
	 * - Contains at least one uppercase letter
	 * - Contains at least one special character from the set [@!#$%^&*]
	 * - Has a length of at least 8 characters
	 *
	 * @param password The password to be validated.
	 * @return true if the password meets the criteria, false otherwise.
	 */
	static bool isPasswordLegal(const std::string& password);

	/**
	 * Checks if an email address is in a valid format.
	 *
	 * This function checks if an email address is in a valid format, adhering to the
	 * standard email address structure:
	 * - The local part can contain alphanumeric characters.
	 * - The domain part must contain at least one dot.
	 * - The domain extension can contain only lowercase alphabets.
	 *
	 * @param email The email address to be validated.
	 * @return true if the email address is in a valid format, false otherwise.
	 */
	static bool isEmailLegal(const std::string& email);

	/**
	 * Checks if an address is in a valid format.
	 *
	 * This function checks if an address is in a valid format, adhering to the standard structure:
	 * - The address consists of a street name, apartment number, and city, separated by spaces.
	 * - The street name and city can contain only alphabets.
	 * - The apartment number can contain only digits.
	 *
	 * @param address The address to be validated.
	 * @return true if the address is in a valid format, false otherwise.
	 */
	static bool isAddressLegal(const std::string& address);
};
