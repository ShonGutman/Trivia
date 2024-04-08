#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include <mutex>
#include "Helper.h"
#include "IRequestHandler.h"

static std::mutex _mutexClients;

constexpr int SERVER_PORT = 8826;
constexpr int MSG_LENGTH = 5;
#define MSG "Hello"

class Communicator
{
public:

	/*
	* ctor of class Communicator
	*/
	Communicator();

	/*
	* dtor of class Communicator
	*/
	~Communicator();
	
	/*
	* function starts the handle proccess of all requests, it listens to clients joining requests and
	* create thread to handle them
	*/
	void startHandleRequests();

private:

	/*
	* function binds listening socket on server socket and listens to clients
	*/
	void bindAndListen();

	/*
	* function handles the acceptence of clients and once accepting user it sends it to a thread
	*/
	void acceptClient();

	/*
	* function handles all requests from a single client
	* @param clientSocket - socket of client to handle
	*/
	void handleNewClient(SOCKET clientSocket);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> _clients;

};