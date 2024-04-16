#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoginManager.h"

// to avoid circular definition
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:

	//CTOR//
	LoginRequestHandler(RequestHandlerFactory& factory);

	bool isRequestRelevant(RequestInfo& info);
	RequestResult handleRequest(RequestInfo& info, LoggedUser& user);

private:

	/**
	 * Handles a login request.
	 *
	 * This function processes a login request received from the client. It deserializes
	 * the request information, validates the login credentials using the LoginManager,
	 * and generates an appropriate response. If the login is successful, it returns a
	 * success response along with a new handler for the menu request. If the login fails,
	 * it returns an error response and remains in the login state.
	 *
	 * @param info The request information containing the login details.
	 * @param user The user the will be logged
	 * @return The result of handling the login request, including the response and the new handler.
	 */
	RequestResult login(RequestInfo& info, LoggedUser& user);

	/**
	 * Handles a signup request.
	 *
	 * This function processes a signup request received from the client. It deserializes
	 * the request information, registers the new user using the LoginManager, and generates
	 * an appropriate response. If the signup is successful, it returns a success response
	 * along with a new handler for the menu request. If the signup fails, it returns an
	 * error response and remains in the login state.
	 *
	 * @param info The request information containing the signup details.
	 * @param user The user the will be signed
	 * @return The result of handling the signup request, including the response and the new handler.
	 */
	RequestResult signup(RequestInfo& info, LoggedUser& user);

	RequestHandlerFactory& _factoryHandler;
};
