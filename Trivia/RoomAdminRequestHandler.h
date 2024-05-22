#pragma once

#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

// to avoid circular definition
class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler(Room&, RoomManager*);

	bool isRequestRelevant(const RequestInfo& info) override;

	RequestResult handleRequest(const RequestInfo& info, LoggedUser user);

private:
	Room _room;
	LoggedUser _user;
	RoomManager& _roomManager;
	RequestHandlerFactory& _factoryHandler;

	RequestResult closeRoom(const RequestInfo& info, LoggedUser user);

	RequestResult startGame(const RequestInfo& info);

	RequestResult getRoomState(const RequestInfo& info);
};
