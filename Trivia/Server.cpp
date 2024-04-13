#include "Server.h"

Server::Server()
{
	_database = new SqliteDatabase();
	_factory = new RequestHandlerFactory(_database);
	_communicator = new Communicator(_factory);
}

Server::~Server()
{
	delete _database;
	delete _factory;
	delete _communicator;
}

void Server::run()
{
	this->_communicator->startHandleRequests();
}
