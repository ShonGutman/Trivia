#include "Server.h"

Server::Server()
{
	_database = new SqliteDatabase();
	_factory = RequestHandlerFactory(_database);
	_communicator = Communicator(&_factory);
}

Server::~Server()
{
	delete _database;
}

void Server::run()
{
	this->_communicator.startHandleRequests();
}
