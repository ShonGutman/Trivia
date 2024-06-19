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
	LOGOUT_REQUEST_ID = 3,
	JOIN_ROOM_REQUEST_ID = 4,
	CREATE_ROOM_REQUEST_ID = 5,
	GET_ALL_ROOMS_REQUEST_ID = 6,
	GET_PLAYERS_IN_ROOM_REQUEST_ID = 7,
	GET_PERSONAL_SCORE_REQUEST_ID = 8,
	GET_HIGHEST_SCORE_REQUEST_ID = 9,
	LEAVE_ROOM_REQUEST_ID = 10,
	CLOSE_ROOM_REQUEST_ID = 11,
	START_GAME_REQUEST_ID = 12,
	GET_ROOM_STATE_REQUEST_ID = 13,
	LEAVE_GAME_REQUEST_ID = 14,
	GET_QUESTION_REQUEST_ID = 15,
	SUBMIT_ANSWER_REQUEST_ID = 16,
	FINISHED_GAME_REQUEST_ID = 17,
	GET_GAME_RESULT_REQUEST_ID = 18,
	SEND_QUESTION_REQUEST_ID = 19,
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

struct SubmitAnswerRequest
{
	unsigned int answerID;
	double timeForAnwser;
};

struct sendQuestionRequest
{
	std::string question;
	std::string correct;
	std::string incorrect1;
	std::string incorrect2;
	std::string incorrect3;

};