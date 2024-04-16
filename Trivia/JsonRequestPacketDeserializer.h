#pragma once

#include "json.hpp"
#include "Requests.h"

using json = nlohmann::json;

#define USERNAME_KEY "username"
#define PASSWORD_KEY "password"
#define EMAIL_KEY "email"
#define ADDRESS_KEY "address"
#define PHONE_NUMBER_KEY "phoneNumber"
#define BIRTHDAY_KEY "birthday"

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
	static LoginRequest deserializeLoginRequest(Buffer& buffer);

	/**
	 * Deserializes a buffer into a SignupRequest object.
	 *
	 * This function parses the data contained in the buffer and constructs a SignupRequest object
	 * based on the information found in the buffer.
	 *
	 * @param buffer The buffer containing the serialized signup request data.
	 * @return The deserialized SignupRequest object.
	 */
	static SignupRequest deserializeSignUpRequest(Buffer& buffer);

private:

	/**
	 * Converts a buffer to a JSON object.
	 *
	 * This function converts the content of the buffer to a JSON object using the nlohmann::json library.
	 *
	 * @param buffer The buffer containing the data to be converted to JSON.
	 * @return A JSON object representing the content of the buffer.
	 */
	static nlohmann::json_abi_v3_11_3::json convertBufferToJson(Buffer& buffer);
};
