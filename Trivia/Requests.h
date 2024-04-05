#pragma once
#include <vector>
#include <ctime>

#include "IRequestHandler.h"

// to avoid circular definition
class IRequestHandler;

using std::tm;

#define BYTE char
typedef std::vector<BYTE> Buffer;

typedef enum RequestId
{
	LOGIN_REQUEST_ID = 1,
	SIGN_UP_REQUEST_ID = 2,
	ERROR_REQUEST_ID = 99
}RequestId;

//general info of a request 
struct RequestInfo
{
	RequestId id;
	tm recivalTime;
	Buffer buffer;
};

//general result of request
struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};


struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};