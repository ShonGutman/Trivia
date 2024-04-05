#pragma once

#include "Responses.h"

class JsonResponsePacketSerializer
{
public:
	static Buffer serializerResponse(ErrorResponse);
	static Buffer serializerResponse(LoginResponse);
	static Buffer serializerResponse(SignupResponse);

private:
	static Buffer decToBin(unsigned int);
};