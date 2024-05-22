#pragma once

#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

// to avoid circular definition
class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room&, RoomManager*);

	bool isRequestRelevant(const RequestInfo& r);

	RequestResult handleRequest(const RequestInfo& r, LoggedUser user);

	RequestResult closeRoom(const RequestInfo& r);

	RequestResult startGame(const RequestInfo& r);

	RequestResult getRoomState(const RequestInfo& r);
private:
	Room _room;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _factoryHandler;
};
