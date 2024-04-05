#pragma once

#include <iostream>
#include <string>

#include "Requests.h"

// to avoid circular definition
struct RequestResult;


class IRequestHandler
{
	virtual bool isRequestRelevant(RequestInfo info) = 0;
	virtual RequestResult handleRequest(RequestInfo info) = 0;
};
