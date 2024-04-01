#pragma once

#include <iostream>
#include <string>
#include "Communicator.h"

class Server
{
public:

	void run();

private:
	Communicator _communicator;

};
