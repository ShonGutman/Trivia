#pragma once

#include <iostream>

typedef struct PlayerResults
{
	std::string username;
	unsigned int numRightAns = 0;

	PlayerResults(const std::string& username, unsigned int numRightAns)
	{
		this->username = username;
		this->numRightAns = numRightAns;
	}

}PlayerResults;
