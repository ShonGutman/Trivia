#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"
#include "LoggedUser.h"

// to avoid circular definition
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:

	MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& factory);

	bool isRequestRelevant(RequestInfo& info);
	RequestResult handleRequest(RequestInfo& info, LoggedUser& user);

private:

	RequestResult logout(RequestInfo& info);

	LoggedUser& _user;
	RequestHandlerFactory& _factoryHandler;
};
