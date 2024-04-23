#pragma once

#include <vector>
#include <string>

#include "Room.h"

#define BYTE unsigned char
typedef std::vector<BYTE> Buffer;

#define STATUS_KEY "status"
#define MESSAGE_KEY "message"

typedef enum : unsigned int {
	LOGIN_RESPONSE_ID = 1,
	SIGN_UP_RESPONSE_ID = 2,
	JOIN_ROOM_RESPONSE_ID = 3,
	CREATE_ROOM_RESPONSE_ID = 4,
	LEAVE_ROOM_RESPONSE_ID = 5,
	GET_ALL_ROOMS_RESPONSE_ID = 6,
	GET_PLAYERS_IN_ROOM_RESPONSE_ID = 7,
	GET_PERSONAL_SCORE_RESPONSE_ID = 8,
	GET_HIGHEST_SCORE_RESPONSE_ID = 9,
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
	ResponseId id = GENERAL_ERROR_RESPONSE_ID;
	std::string message;
}typedef ErrorResponse;

typedef struct LogoutResponse
{
	STATUS status;
}LogoutResponse;

typedef struct GetRoomResponse
{
	STATUS status;
	std::vector<const RoomData> rooms;
}GetRoomResponse;

typedef struct GetPlayersInRoomResponse
{
	std::vector<const std::string> playersInRoom;
}GetPlayersInRoomResponse;

typedef struct GetHighscoreResponse
{
	STATUS status;
	std::vector<const std::string> highScores;
}GetHighscoreResponse;

typedef struct GetPersonalStatsResponse
{
	STATUS status;
	std::vector<const std::string> userStatistics;
}GetPersonalStatsResponse;

typedef struct JoinRoomResponse
{
	STATUS status;
}JoinRoomResponse;

typedef struct CreateRoomResponse
{
	STATUS status;
}CreateRoomResponse;