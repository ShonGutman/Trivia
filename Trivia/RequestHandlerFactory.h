#pragma once

#include "LoginManager.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

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
	 * @param gameRoom Reference to the Room object.
	 * @return A pointer to the newly created RoomAdminRequestHandler instance.
	 */
	RoomAdminRequestHandler* createRoomAdminRequestHandler(Room& gameRoom);

	/**
	* Creates a new RoomMemberRequestHandler instance.
	*
	* This function creates a new RoomMemberRequestHandler instance with the given Room object
	* and returns a pointer to it. Memory management is the responsibility of the caller,
	* and the created object must be deleted when no longer needed.
	*
	* @param gameRoom Reference to the Room object.
	* @return A pointer to the newly created RoomMemberRequestHandler instance.
	*/
	RoomMemberRequestHandler* createRoomMemberRequestHandler(Room& gameRoom);

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

private:
	LoginManager& _loginManager;
	RoomManager& _roomManager;
	StatisticsManager& _statisticsManager;
	IDatabase* _database;
};