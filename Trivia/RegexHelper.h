#pragma once

#include <iostream>
#include <regex>

class RegexHelper
{
public:
	static bool isPasswordLegal(const std::string& password);

	static bool isEmailLegal(const std::string& email);

};
