#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include "IRequestHandler.h"

constexpr int SERVER_PORT = 8826;

class Communicator
{
public:
	
	void startHandleRequests();

private:

	void bindAndListen();

	void handleNewClient();

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> _clients;

};