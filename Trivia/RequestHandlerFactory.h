#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"

// to avoid circular definition
class LoginRequestHandler;

class RequestHandlerFactory
{
	//CTOR//
	RequestHandlerFactory(IDatabase* database);

	/**
	 * Creates a new LoginRequestHandler instance.
	 *
	 * This function creates a new LoginRequestHandler instance and returns a pointer to it.
	 * Memory management is the responsibility of the caller, and the created object must be
	 * deleted when no longer needed.
	 *
	 * @return A pointer to the newly created LoginRequestHandler instance.
	 */
	LoginRequestHandler* createLoginRequestHandler();

	/**
	 * Retrieves the LoginManager instance associated with the RequestHandlerFactory.
	 *
	 * This function returns a reference to the LoginManager instance associated with
	 * the RequestHandlerFactory.
	 *
	 * @return A reference to the LoginManager instance.
	 */
	LoginManager& getLoginManager();

private:
	LoginManager _loginManager;
	IDatabase* _database;
};