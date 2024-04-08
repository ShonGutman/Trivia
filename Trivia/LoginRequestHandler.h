#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler
{
	bool isRequestRelevant(RequestInfo info);
	RequestResult handleRequest(RequestInfo info);
};
