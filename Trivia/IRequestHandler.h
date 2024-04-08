#pragma once

#include <iostream>
#include <string>

#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"

// to avoid circular definition
struct RequestResult;
struct RequestInfo;


class IRequestHandler
{
public:
	/*
	 * Checks if the provided RequestInfo object is relevant to this request handler.
	 * This function is used to determine if the handler should process the request
	 * or not.
	 *
	 * @param info - The RequestInfo object containing information about the request.
	 * @return true if the request is relevant to this handler, false otherwise.
	 */
	virtual bool isRequestRelevant(RequestInfo& info) = 0;

	/*
	 * Handles the incoming request and produces a result based on the provided information.
	 *
	 * @param info The information related to the request.
	 * @return The result of handling the request.
	 */
	virtual RequestResult handleRequest(RequestInfo& info) = 0;
};
