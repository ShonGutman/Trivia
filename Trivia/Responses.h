#pragma once

#include <vector>
#include <set>
#include <string>
#include <map>
#include "Room.h"

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

typedef enum : unsigned int {
	LOGIN_RESPONSE_ID = 1,
	SIGN_UP_RESPONSE_ID = 2,
	LOGOUT_RESPONSE_ID = 3,
	JOIN_ROOM_RESPONSE_ID = 4,
	CREATE_ROOM_RESPONSE_ID = 5,
	GET_ALL_ROOMS_RESPONSE_ID = 6,
	GET_PLAYERS_IN_ROOM_RESPONSE_ID = 7,
	GET_PERSONAL_SCORE_RESPONSE_ID = 8,
	GET_HIGHEST_SCORE_RESPONSE_ID = 9,
	LEAVE_ROOM_RESPONSE_ID = 10,
	CLOSE_ROOM_RESPONSE_ID = 11,
	START_GAME_RESPONSE_ID = 12,
	GET_ROOM_STATE_RESPONSE_ID = 13,
	LEAVE_GAME_RESPONSE_ID = 14,
	GET_QUESTION_RESPONSE_ID = 15,
	SUBMIT_ANSWER_RESPONSE_ID = 16,
	FINISHED_GAME_RESPONSE_ID = 17,
	GET_GAME_RESULTS_RESPONSE_ID = 18,
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

struct LogoutResponse
{
	STATUS status;
}typedef LogoutResponse;

struct ErrorResponse
{
	ResponseId id = GENERAL_ERROR_RESPONSE_ID;
	std::string message;
}typedef ErrorResponse;

typedef struct GetAllRoomsResponse
{
	STATUS status;
	std::vector<RoomData> rooms;
}GetAllRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	STATUS status;
	std::set<LoggedUser> playersInRoom;
}GetPlayersInRoomResponse;

typedef struct GetHighscoreResponse
{
	STATUS status;
	std::map<std::string, unsigned int> highScores; // std::string for the name, int for the score
}GetHighscoreResponse;

typedef struct GetPersonalStatsResponse
{
	STATUS status;
	unsigned int numberOfGames = 0;
	unsigned int numRightAns = 0;
	unsigned int numWrongAns = 0;
	double avgTimeForAns = 0;
}GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	STATUS status;
}JoinRoomResponse;

typedef struct CreateRoomResponse
{
	STATUS status;
}CreateRoomResponse;

typedef struct LeaveRoomResponse
{
	STATUS status;
}LeaveRoomResponse;

typedef struct CloseRoomResponse
{
	STATUS status;
}CloseRoomResponse;

typedef struct StartGameResponse
{
	STATUS status;
}StartGameResponse;

typedef struct GetRoomStatusResponse
{
	STATUS status;
	bool hasGameBegun = false;
	std::set<LoggedUser> players;
}GetRoomStatusResponse;

typedef struct LeaveGameResponse
{
	STATUS status;
}LeaveGameResponse;

typedef struct SubmitAnswerResponse
{
	STATUS status;
	unsigned int correctAnswerID;
}SubmitAnswerResponse;

typedef struct GetQuestionResponse
{
	STATUS status;
	std::string question;
	std::map<unsigned int, std::string> answers;

}GetQuestionResponse;

typedef struct PlayerResults
{
	std::string username;
	unsigned int numRightAns = 0;
	unsigned int numWrongAns = 0;
	double avgTimeForAns = 0;
}PlayerResults;

typedef struct GetGameResultResponse
{
	STATUS status;
	std::vector<PlayerResults> results;
}GetGameResultResponse;

typedef struct FinishedGameResponse
{
	STATUS status;
}FinishedGameResponse;