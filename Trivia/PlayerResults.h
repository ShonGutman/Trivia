#pragma once

#include <iostream>

typedef struct PlayerResults
{
	std::string username;
	unsigned int numRightAns = 0;
	unsigned int numWrongAns = 0;
	double avgTimeForAns = 0;

	PlayerResults(const std::string& username, unsigned int numRightAns,
		unsigned int numWrongAns, double avgTimeForAns)
	{
		this->username = username;
		this->numRightAns = numRightAns;
		this->numWrongAns = numWrongAns;
		this->avgTimeForAns = avgTimeForAns;
	}

}PlayerResults;
