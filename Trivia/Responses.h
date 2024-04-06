#pragma once

#include <vector>

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

#define STATUS "status"
#define MESSAGE "message"

typedef enum : unsigned int {
	LOGIN_RESPONSE_ID = 1,
	SIGN_UP_RESPONSE_ID = 2,
	ERROR_RESPONSE_ID = 99
} ResponseId;

struct LoginResponse
{
	ResponseId status;
}typedef LoginResponse;

struct SignupResponse
{
	ResponseId status;
}typedef SignupResponse;

struct ErrorResponse
{
	std::string message;
}typedef ErrorResponse;
