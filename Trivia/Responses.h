#pragma once

#include <vector>
#include <ctime>
#include <string>

#define BYTE char
typedef std::vector<BYTE> Buffer;

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
