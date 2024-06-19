#pragma once

#include "json.hpp"
#include "Requests.h"

using json = nlohmann::json;

#define USERNAME_KEY "username"
#define PASSWORD_KEY "password"
#define NEW_PASSWORD_KEY "newPassword"
#define EMAIL_KEY "email"
#define ADDRESS_KEY "address"
#define PHONE_NUMBER_KEY "phoneNumber"
#define BIRTHDAY_KEY "birthday"

#define ROOM_ID_KEY "roomId"
#define ROOM_NAME_KEY "roomName"
#define MAX_PLAYERS_IN_ROOM_KEY "playersNum"
#define NUM_OF_QUESTIONS_IN_GAME_KEY "questionNum"
#define TINE_PER_QUESTION_KEY "timePerQuestion"

#define ANSWER_ID_KEY "answerID"
#define ANSWER_RESPONSE_TIME "timeForAnswer"

#define QUESTION_KEY "question"
#define CORRECT_KEY "correct"
#define INCORRECT1_KEY "incorrect1"
#define INCORRECT2_KEY "incorrect2"
#define INCORRECT3_KEY "incorrect3"

#define SIZE_BYTE 8
#define MSG_MAX_SIZE 4

class JsonRequestPacketDeserializer
{
public:

	/**
	 * Deserializes a buffer into a LoginRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a LoginRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized login request data.
	 * @return The deserialized LoginRequest object.
	 */
	static LoginRequest deserializeLoginRequest(const Buffer& buffer);

	/**
	 * Deserializes a buffer into a SignupRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a SignupRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized signup request data.
	 * @return The deserialized SignupRequest object.
	 */
	static SignupRequest deserializeSignUpRequest(const Buffer& buffer);

	/**
	 * Deserialize a buffer into a GetPlayersInRoomRequest object.
	 * 
	 * This function parses the data contained in the buffer and constructs a GetPlayersInRoomRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized data.
	 * @return A GetPlayersInRoomRequest object deserialized from the buffer.
	 */
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const Buffer& buffer);

	/**
	 * Deserialize a buffer into a JoinRoomRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a JoinRoomRequest object
	 * based on the information found in the buffer.
	 * 
	 * @param buffer The buffer containing the serialized data.
	 * @return A JoinRoomRequest object deserialized from the buffer.
	 */
	static JoinRoomRequest deserializeJoinRoomRequest(const Buffer& buffer);

	/**
	 * Deserialize a buffer into a CreateRoomRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a CreateRoomRequest object
	 * based on the information found in the buffer.
	 * 
	 * @param buffer The buffer containing the serialized data.
	 * @return A CreateRoomRequest object deserialized from the buffer.
	 */
	static CreateRoomRequest deserializeCreateRoomRequest(const Buffer& buffer);

	/**
	 * Deserialize a buffer into a SubmitAnswerRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a SubmitAnswerRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized data.
	 * @return A SubmitAnswerRequest object deserialized from the buffer.
	 */
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const Buffer& buffer);

	/**
	 * Deserialize a buffer into a sendQuestionRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a sendQuestionRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized data.
	 * @return A sendQuestionRequest object deserialized from the buffer.
	 */
	static sendQuestionRequest deserializeSendQuestionRequest(const Buffer& buffer);

	/**
	 * Deserialize a buffer into a ChangePasswordRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a ChangePasswordRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized data.
	 * @return A ChangePasswordRequest object deserialized from the buffer.
	 */
	static ChangePasswordRequest deserializeChangePasswordRequest(const Buffer& buffer);

private:

	/**
	 * Converts a buffer to a JSON object.
	 *
	 * This function converts the content of the buffer to a JSON object using the nlohmann::json library.
	 *
	 * @param buffer The buffer containing the data to be converted to JSON.
	 * @return A JSON object representing the content of the buffer.
	 */
	static nlohmann::json_abi_v3_11_3::json convertBufferToJson(const Buffer& buffer);
};
