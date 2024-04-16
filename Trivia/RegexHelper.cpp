#include "RegexHelper.h"

bool RegexHelper::isPasswordLegal(const std::string& password)
{
	//using positive lookaheads to check if password contains:
	//at least one number, small letter, large letter, speacial char
	//password length must be 8
	const std::regex expression("^(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[\@\!\#\$\%\^\&\*]).{8}$");
		
	return std::regex_match(password, expression);
}

bool RegexHelper::isEmailLegal(const std::string& email)
{
	//email looks like this:
	//start@domain.extension.again
	const std::regex expression("^[\da-zA-Z]+@[a-zA-Z]+(\.[a-z]+)+$");

	return std::regex_match(email, expression);
}

bool RegexHelper::isAddressLegal(const std::string& address)
{
	//address is like this:
	// Street (space) Apt (space) City
	//credit: https://stackoverflow.com/questions/24744819/does-stdregex-support-i-for-case-insensitivity
	const std::regex expression("^[a-z]+\s[\d]+\s[a-z]+$", std::regex_constants::icase);

	return std::regex_match(address, expression);
}

bool RegexHelper::isPhoneNumberLegal(const std::string& phoneNumber)
{
	//phone number looks like this:
	//0XY-XXXXXXX (Y is optional)
	const std::regex expression("^0\d{1,2}-\d{7}$");

	return std::regex_match(phoneNumber, expression);
}

bool RegexHelper::isBirthdayLegal(const std::string& birthday)
{
	//birthday looks like this:
	//DD.MM.YYYY or DD/MM/YYYY
	const std::regex expression("^\d{2}([\. | \/])\d{2}\1\d{4}$");

	return std::regex_match(birthday, expression);
}
