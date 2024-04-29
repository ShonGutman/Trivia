#pragma once

#include "Responses.h"
#include "json.hpp"

#include <ctime>
#include <string>

using json = nlohmann::json;

#define SIZE_BYTE 8
#define MSG_MAX_SIZE 4

#define STATUS_KEY "status"
#define MESSAGE_KEY "message"
#define ROOMS_KEY "Rooms"
#define PLAYERS_IN_ROOM_KEY "PlayersInRoom"
#define USER_STATISTICS_KEY "UserStatistics"
#define HIGHSCORES_KEY "HighScores"

#define ID "id"
#define NAME "name"
#define MAX_PLAYERS "maxPlayers"
#define NUM_OF_QUESTION_IN_GAME "numOfQuestionsInGame"
#define TIME_PER_QUESTION "timePerQuestion"
#define IS_ACTIVE "isActive"

class JsonResponsePacketSerializer
{
public:
	/*
	* Serializes an error response into a binary buffer.
	* @param response: The ErrorResponse& object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializerResponse(ErrorResponse& response);

	/*
	* Serializes a login response into a binary buffer.
	* @param response: The LoginResponse object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializerResponse(LoginResponse& response);

	/*
	* Serializes a signup response into a binary buffer.
	* @param response: The SignupResponse object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializerResponse(SignupResponse& response);

	/*
	* Serializes a logout response into a binary buffer.
	* @param response: The LogoutResponse object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializeLogoutResponse(LogoutResponse& response);

	/**
	 * Serializes a LeaveRoomResponse into a Buffer.
	 *
	 * @param response The LeaveRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializeLeaveRoomResponse(LeaveRoomResponse& response);

	/**
	 * Serializes a GetRoomResponse into a Buffer.
	 *
	 * @param response The GetRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializeGetRoomResponse(GetAllRoomsResponse& response);

	/**
	 * Serializes a GetPlayersInRoomResponse into a Buffer.
	 *
	 * @param response The GetPlayersInRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse& response);

	/**
	 * Serializes a JoinRoomResponse into a Buffer.
	 *
	 * @param response The JoinRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializeJoinRoomResponse(JoinRoomResponse& response);

	/**
	 * Serializes a CreateRoomResponse into a Buffer.
	 *
	 * @param response The CreateRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializeCreateRoomResponse(CreateRoomResponse& response);

	/**
	 * Serializes Highscore and PersonalStats responses into a Buffer.
	 *
	 * @param highscoreResponse The HighscoreResponse to serialize.
	 * @param personalStatsResponse The PersonalStatsResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializeHighScoreResponse(GetHighscoreResponse& highscoreResponse,
		GetPersonalStatsResponse& personalStatsResponse);



private:
	/*
	* Converts a decimal number to its binary representation.
	* @param decNum: The decimal number to be converted to binary.
	* @return: The binary buffer containing the binary representation of the decimal number.
	*/
	static Buffer decToBin(unsigned int decNum);

	/*
	* Converts a string to its binary representation.
	* @param str: The string to be converted to binary.
	* @return: The binary buffer containing the binary representation of the string.
	*/
	static Buffer strToBin(std::string str);

	/*
	* Fits a message and a code into a binary buffer according to the protocol.
	* @param msg: The message string to be included in the buffer.
	* @param code: The code representing the message type.
	* @return: The binary buffer containing the message and code formatted according to the protocol.
	*/
	static Buffer fitBuffToProtocol(std::string msg, ResponseId code);

	/**
	 * Converts a vector of RoomData objects into a JSON object.
	 *
	 * @param roomVec The vector containing RoomData objects to be converted.
	 * @return A JSON object representing the converted RoomData objects.
	 */
	static nlohmann::json_abi_v3_11_3::json convertObjectToJson(const std::vector<RoomData>& roomVec);

	/**
	 * Converts a vector of strings into a JSON array.
	 *
	 * @param stringVec The vector containing strings to be converted.
	 * @return A JSON array representing the converted strings.
	 */
	static nlohmann::json_abi_v3_11_3::json convertObjectToJson(const std::vector<std::string>& stringVec);


};
