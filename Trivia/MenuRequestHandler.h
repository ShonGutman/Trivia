#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler
{
public:

	bool isRequestRelevant(RequestInfo& info);
	RequestResult handleRequest(RequestInfo& info);
};
