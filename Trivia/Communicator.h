#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include "IRequestHandler.h"

static std::mutex _mutexClients;

constexpr int SERVER_PORT = 8826;

class Communicator
{
public:
	
	void startHandleRequests();

private:

	void bindAndListen();

	/*
	* function handles the acceptence of clients and once accepting user it sends it to a thread
	*/
	void acceptClient();

	void handleNewClient(SOCKET clientSocket);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> _clients;

};