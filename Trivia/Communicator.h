#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <string>
#include <map>
#include <thread>
#include "Helper.h"
#include "LoginRequestHandler.h"
#include "RequestHandlerFactory.h"


constexpr int SERVER_PORT = 8826;
constexpr int CODE_LENGTH_IN_BYTES = 1;
constexpr int MSG_LENGTH_IN_BYTES = 4;

class Communicator
{
public:

	//CTOR//
	Communicator();
	Communicator(RequestHandlerFactory* factory);

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

	/**
	 * Scans the incoming request from the specified client socket and extracts the relevant information.
	 *
	 * This function reads the incoming request from the client socket and extracts the relevant
	 * information to construct a RequestInfo object.
	 *
	 * @param clientSocket The socket from which to read the request.
	 * @return The RequestInfo object containing the extracted information from the request.
	 */
	static RequestInfo scanRequest(SOCKET clientSocket);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> _clients;
	RequestHandlerFactory* _factory;

};