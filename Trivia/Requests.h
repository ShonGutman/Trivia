#pragma once
#include <vector>
#include <ctime>

#include "IRequestHandler.h"

// to avoid circular definition
class IRequestHandler;

using std::tm;

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

typedef enum : unsigned int
{
	LOGIN_REQUEST_ID = 1,
	SIGN_UP_REQUEST_ID = 2,
	ERROR_REQUEST_ID = 99
}RequestId;

//general info of a request 
struct RequestInfo
{
	//by deafult id is error
	RequestId id = ERROR_REQUEST_ID;
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
	std::string address;
	std::string phoneNumber;
	std::string birthday;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomID;
};

struct JoinRoomRequest
{
	unsigned int roomID;
};

struct CreateRoomRequest
{
	std::string roomName;
	unsigned int maxPlayers;
	unsigned int numOfQuestionsInGame;
	unsigned int timePerQuestion;
};