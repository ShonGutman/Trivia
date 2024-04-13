#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

// to avoid circular definition
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:

	//CTOR//
	LoginRequestHandler(RequestHandlerFactory& factory);

	bool isRequestRelevant(RequestInfo& info);
	RequestResult handleRequest(RequestInfo& info);

private:
	RequestHandlerFactory& _factoryHandler;
};
