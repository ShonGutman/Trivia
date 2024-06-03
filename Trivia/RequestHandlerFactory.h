#pragma once

#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

// to avoid circular definition
class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;

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
	MenuRequestHandler* createMenuRequestHandler();

	/**
	 * Creates a new RoomAdminRequestHandler instance.
	 *
	 * This function creates a new RoomAdminRequestHandler instance with the given Room object
	 * and returns a pointer to it. Memory management is the responsibility of the caller,
	 * and the created object must be deleted when no longer needed.
	 *
	 * @param gameRoomID id to the Room object.
	 * @return A pointer to the newly created RoomAdminRequestHandler instance.
	 */
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const unsigned int gameRoomID);

	/**
	* Creates a new RoomMemberRequestHandler instance.
	*
	* This function creates a new RoomMemberRequestHandler instance with the given Room object
	* and returns a pointer to it. Memory management is the responsibility of the caller,
	* and the created object must be deleted when no longer needed.
	*
	* @param gameRoomID id to the Room object.
	* @return A pointer to the newly created RoomMemberRequestHandler instance.
	*/
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const unsigned int gameRoomID);

	GameRequestHandler* createGameRequestHandler(const Room& room);

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

	/**
	 * Retrieves the StatisticsManager instance associated with the RequestHandlerFactory.
	 *
	 * This function returns a reference to the StatisticsManager instance associated with
	 * the RequestHandlerFactory.
	 *
	 * @return A reference to the StatisticsManager instance.
	 */
	StatisticsManager& getStatisticsManager();

	/**
	 * Retrieves the GameManager instance associated with the RequestHandlerFactory.
	 *
	 * This function returns a reference to the GameManager instance associated with
	 * the RequestHandlerFactory.
	 *
	 * @return A reference to the GameManager instance.
	 */
	GameManager& getGameManager();

private:
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
	GameManager& _gameManager;
	IDatabase* _database;
};