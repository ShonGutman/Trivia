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

typedef struct LeaveRoomResponse
{
	STATUS status;
}LeaveRoomResponse;

typedef struct GetAllRoomsResponse
{
	STATUS status;
	std::vector<RoomData> rooms;
}GetAllRoomsResponse;

typedef struct GetPlayersInRoomResponse
{
	STATUS status;
	std::set<LoggedUser> playersInRoom;
	LoggedUser roomAdmin;
}GetPlayersInRoomResponse;

typedef struct GetHighscoreResponse
{
	STATUS status;
	std::map<std::string, int> highScores; // std::string for the name, int for the high score
}GetHighscoreResponse;

typedef struct GetPersonalStatsResponse
{
	STATUS status;
	int numberOfGames;
	int numRightAns;
	int numWrongAns;
	double avgTimeForAns;
}GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	STATUS status;
}JoinRoomResponse;

typedef struct CreateRoomResponse
{
	STATUS status;
}CreateRoomResponse;