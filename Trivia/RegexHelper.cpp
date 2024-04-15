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
	const std::regex expression("^[\da-zA-Z]+@[\da-zA-Z]+(\.[a-z]+)+$");

	return std::regex_match(email, expression);
}
