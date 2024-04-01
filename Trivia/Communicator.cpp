#include "Communicator.h"

Communicator::Communicator()
	:_clients()
{
	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	// if the server use UDP we will use: SOCK_DGRAM & IPPROTO_UDP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
		_clients.clear();
	}
	catch (...) {}
}

void Communicator::startHandleRequests()
{
	bindAndListen();

	while (true)
	{
		// main thread is only accepting clients 
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(SERVER_PORT); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << SERVER_PORT << std::endl;
}

void Communicator::acceptClient()
{
	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__);
	}

	std::cout << "Client accepted. Server and client can speak" << std::endl;

	// create thread that handels the new client
	std::thread t(&Communicator::handleNewClient, this, client_socket);
	t.detach();
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	std::string msg;
	try
	{
		msg = getMsgFromSocket(clientSocket, MSG_LENGTH);
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
		closesocket(clientSocket);
		return;
	}

	if (strncmp(msg.c_str(), MSG, MSG_LENGTH) != 0)
	{
		closesocket(clientSocket);
		throw std::exception("Client Msg doesn't match expected msg");
	}

	sendData(clientSocket, MSG);
}

void Communicator::sendData(SOCKET clientSocket, const std::string& message)
{
	const char* data = message.c_str();

	if (send(clientSocket, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}

std::string Communicator::getMsgFromSocket(SOCKET clientSocket, const int bytesNum)
{
		char* msg = getMsgFromSocket(clientSocket, bytesNum, 0);
		std::string s(msg);

		//remove allocated memory
		delete msg;

		return s;
}

char* Communicator::getMsgFromSocket(SOCKET clientSocket, const int bytesNum, const int flags)
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
