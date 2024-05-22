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
	RoomAdminRequestHandler(RequestHandlerFactory& factory, Room& gameRoom);

	bool isRequestRelevant(const RequestInfo& info) override;

	RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:
	Room& _room;
	RequestHandlerFactory& _factoryHandler;

	RequestResult closeRoom(const RequestInfo& info, LoggedUser& user);

	RequestResult startGame(const RequestInfo& info, LoggedUser& user);

	RequestResult getRoomState(const RequestInfo& info, LoggedUser& user);
};
