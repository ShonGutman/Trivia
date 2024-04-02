#include "Server.h"

void Server::run()
{
	this->_communicator.startHandleRequests();
}
