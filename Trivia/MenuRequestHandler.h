#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "LoggedUser.h"

// to avoid circular definition
class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:

	MenuRequestHandler(RequestHandlerFactory& factory);

	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:

	/*
	* Handles a logout request by logging out the specified user.
	*
	* @param info The request information, such as request type and data.
	* @param user The logged-in user to be logged out.
	* @return RequestResult containing the response to the logout request and the next handler to be used.
	*         If the logout is successful, a success response is returned along with a new handler for the
	*         login request. If the logout fails, an error response is returned, and the current assian nullptr
	*         handler to remove that suspicious user.
	*/
	RequestResult logout(const RequestInfo& info, LoggedUser& user);

	/*
	* Processes a join room request by adding the specified user to the identified room.
	* It deserializes the request information to extract the room ID, then attempts to add
	* the user to the room using the RoomManager. If successful, it returns a success response
	* with the current menu handler. If the operation fails (e.g., room not found, user already
	* in the room), it returns an error response and maintains the current menu handler.
	*
	* @param info The request information, including the serialized data representing the room ID.
	* @param user The logged-in user requesting to join the room.
	* @return RequestResult containing the response to the join room request and the next handler to be used.
	*/
	RequestResult joinRoom(const RequestInfo& info, const LoggedUser& user);

	/*
	* Processes a request to create a new room initiated by the specified user. It deserializes
	* the request information to extract details about the new room, then attempts to create
	* the room using the RoomManager. If successful, it returns a success response with the
	* current menu handler. If the operation fails (e.g., invalid parameters), an error response
	* is returned, and the current menu handler is maintained.
	*
	* @param info The request information, including the serialized data representing the room details.
	* @param user The logged-in user creating the room.
	* @return RequestResult containing the response to the create room request and the next handler to be used.
	*/
	RequestResult createRoom(const RequestInfo& info, const LoggedUser& user);

	RequestResult leaveRoom(const RequestInfo& info, const LoggedUser& user);

	RequestHandlerFactory& _factoryHandler;
};
