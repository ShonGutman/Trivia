#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& factory, Room& gameRoom)
	:_factoryHandler(factory), _room(gameRoom)
{
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id == CLOSE_ROOM_REQUEST_ID || info.id == START_GAME_REQUEST_ID ||info.id == GET_ROOM_STATE_REQUEST_ID;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
	switch (info.id)
	{
	case START_GAME_REQUEST_ID:
		return this->startGame(info, user);
		break;
	case CLOSE_ROOM_REQUEST_ID:
		return this->closeRoom(info, user);
		break;
	case GET_ROOM_STATE_REQUEST_ID:
		return this->getRoomState(info, user);
		break;

	default:
		throw std::runtime_error("Illegal option!");
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info, LoggedUser& user)
{
	RequestResult result;

	RoomManager& RoomManager = _factoryHandler.getRoomManager();

	try
	{
		CloseRoomResponse response;
		RoomManager.deleteRoom(this->_room.getRoomData().id);

		//SUCCESS reponse to close room
		response.status = SUCCESS;

		//assign to MenuHandler 
		result.newHandler = _factoryHandler.createMenuRequestHandler();
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}
	catch (const std::exception& e)
	{
		ErrorResponse response;

		//FAILED reponse to login
		response.message = e.what();
		response.id = CLOSE_ROOM_RESPONSE_ID;

		//assign to LoginHandler
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(this->_room);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

	return result;
}

