#pragma once

#include <string>
#include <vector>
#include <WinSock2.h>

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

class Helper
{
public:

	/**
	 * Retrieves an integer code from the message received on the specified client socket.
	 *
	 * This function reads the specified amount of bytes from the client socket and interprets
	 * them as an integer code.
	 *
	 * @param clientSocket The socket from which to read the message.
	 * @param amountOfBytes The number of bytes to read from the message.
	 * @return The integer code extracted from the message.
	 */
	static int getMessageIntCode(SOCKET clientSocket, unsigned int amountOfBytes);

	/*
	* send msg to client
	* @param clientSocket - socket of client
	* @param message - msg to send to client
	*/
	static void sendData(SOCKET clientSocket, const Buffer& bufferMessage);

	/*
	* function reads data in clientSocket
	* @param clientSocket - socket of client to read
	* @param bytesNum - amount of bytes to read
	* @return: readed data as buffer
	*/
	static Buffer getMsgFromSocket(SOCKET clientSocket, const int bytesNum);

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