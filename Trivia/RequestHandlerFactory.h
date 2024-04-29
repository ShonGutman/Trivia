#pragma once

#include "LoginManager.h"
#include "RoomManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

// to avoid circular definition
class LoginRequestHandler;

class RequestHandlerFactory
{
public:

	//CTOR//
	RequestHandlerFactory() = default;
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
	 * Creates a new MenuRequestHandler instance.
	 *
	 * This function creates a new MenuRequestHandler instance and returns a pointer to it.
	 * Memory management is the responsibility of the caller, and the created object must be
	 * deleted when no longer needed.
	 *
	 * @return A pointer to the newly created MenuRequestHandler instance.
	 */
	MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);

	/**
	 * Retrieves the LoginManager instance associated with the RequestHandlerFactory.
	 *
	 * This function returns a reference to the LoginManager instance associated with
	 * the RequestHandlerFactory.
	 *
	 * @return A reference to the LoginManager instance.
	 */
	LoginManager& getLoginManager();

	/**
	 * Retrieves the RoomManager instance associated with the RequestHandlerFactory.
	 *
	 * This function returns a reference to the RoomManager instance associated with
	 * the RequestHandlerFactory.
	 *
	 * @return A reference to the RoomManager instance.
	 */
	RoomManager& getRoomManager();

private:
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	IDatabase* _database;
};