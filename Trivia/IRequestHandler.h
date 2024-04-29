#pragma once

#include <iostream>
#include <string>

#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoggedUser.h"

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
	virtual bool isRequestRelevant(const RequestInfo& info) = 0;

	/*
	 * Handles the incoming request and produces a result based on the provided information.
	 *
	 * @param info The information related to the request.
	 * @param user The user the is logged
	 * @return The result of handling the request.
	 */
	virtual RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) = 0;
};
