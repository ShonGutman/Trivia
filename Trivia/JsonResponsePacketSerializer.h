#pragma once

#include "Responses.h"

class JsonResponsePacketSerializer
{
public:
	/*
	* Serializes an error response into a binary buffer.
	* @param response: The ErrorResponse object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializerResponse(ErrorResponse response);

	/*
	* Serializes a login response into a binary buffer.
	* @param response: The LoginResponse object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializerResponse(LoginResponse response);

	/*
	* Serializes a signup response into a binary buffer.
	* @param response: The SignupResponse object to be serialized.
	* @return: The binary buffer containing the serialized response.
	*/
	static Buffer serializerResponse(SignupResponse response);

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
	static Buffer fitBuffToProtocol(std::string msg, unsigned int code);

};
