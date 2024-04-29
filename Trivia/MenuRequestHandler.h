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

	MenuRequestHandler(RequestHandlerFactory& factory);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:

	RequestResult logout(const RequestInfo& info);

	RequestHandlerFactory& _factoryHandler;
};
