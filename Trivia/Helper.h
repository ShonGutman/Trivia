#pragma once

#include <string>
#include <vector>
#include <WinSock2.h>

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

#define MSG_MAX_SIZE 4

class Helper
{
public:

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
	static Buffer getMsgFromSocket(SOCKET clientSocket, const unsigned int bytesNum);

	/*
	* function reads length in clientSocket
	* @param clientSocket - socket of client to read
	* @return: readed length as buffer
	*/
	static Buffer getLengthFromSocket(SOCKET clientSocket);

	/*
	* --------------------------------------------------------------------------------------------
	* this function is helper to std::string getMsgFromSocket(SOCKET clientSocket, int bytesNum);
	* it is better to use that function because it is easier and safer (secures usage of memory)
	* --------------------------------------------------------------------------------------------
	* this function reads bytesNum of chars for clientSocket and returns the data.
	* note: returned data in allocatead in the heap! so it must be deleted!
	* @return: readed data
	*/
	static char* getMsgFromSocket(SOCKET clientSocket, const unsigned int bytesNum, const unsigned int flags);


	/**
	 * Converts a binary buffer to its decimal representation.
	 *
	 * This function takes a buffer containing binary data and converts it to its equivalent
	 * decimal representation.
	 *
	 * @param buffer The buffer containing the binary data to be converted.
	 * @return The decimal representation of the binary data.
	 */
	static unsigned int binToDec(const Buffer buffer);
};