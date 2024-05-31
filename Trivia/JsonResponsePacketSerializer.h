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
#define HIGHSCORES_KEY "HighScore"

#define ROOM_ID_KEY "roomId"
#define ROOM_NAME_KEY "roomName"
#define MAX_PLAYERS_IN_ROOM_KEY "playersNum"
#define NUM_OF_QUESTIONS_IN_GAME_KEY "questionNum"
#define TINE_PER_QUESTION_KEY "timePerQuestion"
#define IS_ACTIVE_KEY "isActive"



#define NUMBER_OF_GAMES_KEY "numGames"
#define NUMBER_OF_RIGHT_ANS_KEY "numRightAnswers"
#define NUMBER_OF_WRONG_ANS_KEY "numWrongAnswers"
#define AVG_TIME_FOR_ANS_KEY "averageTimeForAnswer"

#define HAS_GAME_BEGUN_KEY "hasGameBegun"



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
	static Buffer serializerResponse(LogoutResponse& response);

	/**
	 * Serializes a GetRoomResponse into a Buffer.
	 *
	 * @param response The GetRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializerResponse(GetAllRoomsResponse& response);

	/**
	 * Serializes a GetPlayersInRoomResponse into a Buffer.
	 *
	 * @param response The GetPlayersInRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializerResponse(GetPlayersInRoomResponse& response);

	/**
	 * Serializes a JoinRoomResponse into a Buffer.
	 *
	 * @param response The JoinRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializerResponse(JoinRoomResponse& response);

	/**
	 * Serializes a CreateRoomResponse into a Buffer.
	 *
	 * @param response The CreateRoomResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializerResponse(CreateRoomResponse& response);

	/**
	 * Serializes Highscore and PersonalStats responses into a Buffer.
	 *
	 * @param highscoreResponse The HighscoreResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializerResponse(GetHighscoreResponse& response);

	/**
	 * Serializes Highscore and PersonalStats responses into a Buffer.
	 *
	 * @param personalStatsResponse The PersonalStatsResponse to serialize.
	 * @return A Buffer containing the serialized data.
	 */
	static Buffer serializerResponse(GetPersonalStatsResponse& response);

	/*
	* Serializes a LeaveRoomResponse object into a buffer for transmission. It constructs a JSON object
	* containing the response status and then converts it to a string representation. Finally, it adjusts
	* the buffer to fit the protocol requirements and returns it.
	*
	* @param response The LeaveRoomResponse object to be serialized.
	* @return Buffer containing the serialized response ready for transmission.
	*/
	static Buffer serializerResponse(LeaveRoomResponse& response);

	/*
	* Serializes a CloseRoomResponse object into a buffer for transmission. It constructs a JSON object
	* containing the response status and then converts it to a string representation. Finally, it adjusts
	* the buffer to fit the protocol requirements and returns it.
	*
	* @param response The CloseRoomResponse object to be serialized.
	* @return Buffer containing the serialized response ready for transmission.
	*/

	static Buffer serializerResponse(CloseRoomResponse& response);

	/*
	* Serializes a StartGameResponse object into a buffer for transmission. It constructs a JSON object
	* containing the response status and then converts it to a string representation. Finally, it adjusts
	* the buffer to fit the protocol requirements and returns it.
	*
	* @param response The StartGameResponse object to be serialized.
	* @return Buffer containing the serialized response ready for transmission.
	*/

	static Buffer serializerResponse(StartGameResponse& response);

	/*
	* Serializes a GetRoomStatusResponse object into a buffer for transmission. It constructs a JSON object
	* containing the response status, whether the game has begun, and the list of players in the room. It converts
	* the player objects into JSON format using a helper function. Finally, it adjusts the buffer to fit the protocol
	* requirements and returns it.
	*
	* @param response The GetRoomStatusResponse object to be serialized.
	* @return Buffer containing the serialized response ready for transmission.
	*/

	static Buffer serializerResponse(GetRoomStatusResponse& response);



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
	 * Converts a set of LoggedUser into a JSON array.
	 *
	 * @param LoggedSet The set containing LoggedUser to be converted.
	 * @return A JSON array representing the converted LoggedUser.
	 */
	static nlohmann::json_abi_v3_11_3::json convertObjectToJson(const std::set<LoggedUser>& LoggedSet);

	/**
	 * Converts a map of strings and int into a JSON array.
	 *
	 * @param scoresMap The map containing strings to be converted.
	 * @return A JSON array representing the converted strings.
	 */
	static nlohmann::json_abi_v3_11_3::json convertObjectToJson(const std::map<std::string, int>& scoresMap);

	/**
	 * Converts a struct of GetPersonalStatsResponse into a JSON array.
	 *
	 * @param presonalStatsStruct The struct containing strings to be converted.
	 * @return A JSON array representing the converted struct.
	 */
	static nlohmann::json_abi_v3_11_3::json convertObjectToJson(const GetPersonalStatsResponse& presonalStatsStruct);

};
