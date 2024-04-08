#include "Helper.h"

int Helper::getMessageIntCode(SOCKET clientSocket, unsigned int amountOfBytes)
{
	std::string msgTypeAsString = getMsgFromSocket(clientSocket, amountOfBytes);

	if (msgTypeAsString == "")
	{
		return 0;
	}

	return std::atoi(msgTypeAsString.c_str());
}

void Helper::sendData(SOCKET clientSocket, const Buffer& bufferMessage)
{
	//convert buffer to string
	std::string message(bufferMessage.begin(), bufferMessage.end());

	const char* data = message.c_str();

	if (send(clientSocket, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

Buffer Helper::getMsgFromSocket(SOCKET clientSocket, const int bytesNum)
{
	char* msg = getMsgFromSocket(clientSocket, bytesNum, 0);
	std::string msgString(msg);

	//convert string to buffer
	Buffer msgBuffer(msgString.begin(), msgString.end());

	//remove allocated memory
	delete msg;

	return msgBuffer;
}

char* Helper::getMsgFromSocket(SOCKET clientSocket, const int bytesNum, const int flags)
{
	if (bytesNum == 0)
	{
		return (char*)"";
	}

	char* data = new char[bytesNum + 1];
	int res = recv(clientSocket, data, bytesNum, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(clientSocket);
		throw std::exception(s.c_str());
	}

	data[bytesNum] = 0;
	return data;
}