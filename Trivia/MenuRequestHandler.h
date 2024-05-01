#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

// to avoid circular definition
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:

	MenuRequestHandler(RequestHandlerFactory& factory);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:

	/*
	* Handles a logout request by logging out the specified user.
	*
	* @param info The request information, such as request type and data.
	* @param user The logged-in user to be logged out.
	* @return RequestResult containing the response to the logout request and the next handler to be used.
	*         If the logout is successful, a success response is returned along with a new handler for the
	*         login request. If the logout fails, an error response is returned, and the current assian nullptr
	*         handler to remove that suspicious user.
	*/
	RequestResult logout(const RequestInfo& info, LoggedUser& user);

	RequestResult joinRoom(const RequestInfo& info, const LoggedUser& user);

	RequestHandlerFactory& _factoryHandler;
};
