#pragma once

#include <iostream>
#include <string>
#include "Communicator.h"

class Server
{
public:

	/*
	* function starts server
	*/
	void run();

private:
	Communicator _communicator;

};
