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
constexpr int MSG_LENGTH = 5;
constexpr const char* MSG = "Hello";

class Communicator
{
public:
	
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

	/*
	* send msg to client
	* @param clientSocket - socket of client
	*/
	static void sendData(SOCKET clientSocket, const std::string& message);

	/*
	* function reads data in clientSocket
	* @param clientSocket - socket of client to read
	* @param bytesNum - amount of bytes to read
	* @return: readed data
	*/
	static std::string getMsgFromSocket(SOCKET clientSocket, const int bytesNum);

	/*
	* --------------------------------------------------------------------------------------------
	* this function is helper to std::string getMsgFromSocket(SOCKET clientSocket, int bytesNum);
	* it is better to use that function because it is easier and safer (secures usage of memory) 
	* --------------------------------------------------------------------------------------------
	* this function reads bytesNum of chars for clientSocket and returns the data.
	* note: returned data in allocatead in the heap! so it must be deleted!
	* @return: readed data
	*/
	static char* getMsgFromSocket(SOCKET clientSocket, const int bytesNum, const int flags);

	SOCKET _serverSocket;
	std::map<SOCKET, IRequestHandler*> _clients;

};