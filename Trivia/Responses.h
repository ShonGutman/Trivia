#pragma once

#include <vector>
#include <string>

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

#define STATUS_KEY "status"
#define MESSAGE_KEY "message"

typedef enum : unsigned int {
	LOGIN_RESPONSE_ID = 1,
	SIGN_UP_RESPONSE_ID = 2,
	GENERAL_ERROR_RESPONSE_ID = 99
} ResponseId;

typedef enum : unsigned int
{
	SUCCESS = 100,
	FAILED = 101
}STATUS;

struct LoginResponse
{
	STATUS status;
}typedef LoginResponse;

struct SignupResponse
{
	STATUS status;
}typedef SignupResponse;

struct ErrorResponse
{
	ResponseId id;
	std::string message;
}typedef ErrorResponse;
