#pragma once

#include <string>
#include <WinSock2.h>

class Helper
{
public:

	/*
	* send msg to client
	* @param clientSocket - socket of client
	* @param message - msg to send to client
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
};