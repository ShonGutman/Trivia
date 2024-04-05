#pragma once

#include <vector>
#include <ctime>
#include <string>

#include "json.hpp"

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

#define STATUS "status"
#define MESSAGE "message"

typedef enum ResponseId
{
	LOGIN_RESPONSE_ID = 1,
	SIGN_UP_RESPONSE_ID = 2,
	ERROR_RESPONSE_ID = 99
}ResponseId;

struct LoginResponse
{
	unsigned int status;
}typedef LoginResponse;

struct SignupResponse
{
	unsigned int status;
}typedef SignupResponse;

struct ErrorResponse
{
	std::string message;
}typedef ErrorResponse;
