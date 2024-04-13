#pragma once

#include <iostream>
#include <string>
#include "Communicator.h"
#include "RequestHandlerFactory.h"
#include "IDatabase.h"
#include "SqliteDatabase.h"

class Server
{
public:

	//CTOR//
	Server();

	//DTOR//
	~Server();

	/*
	* function starts server
	*/
	void run();

private:
	Communicator _communicator;
	RequestHandlerFactory _factory;
	IDatabase* _database;
};
