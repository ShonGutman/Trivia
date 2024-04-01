#include "Communicator.h"

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

}
