#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id == CLOSE_ROOM_REQUEST_ID || info.id == START_GAME_REQUEST_ID ||info.id == GET_ROOM_STATE_REQUEST_ID;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& info, LoggedUser user)
{
	switch (info.id)
	{
	case START_GAME_REQUEST_ID:
		return this->startGame(info);
		break;
	case CLOSE_ROOM_REQUEST_ID:
		return this->closeRoom(info, user);
		break;
	case GET_ROOM_STATE_REQUEST_ID:
		return this->getRoomState(info);
		break;

	default:
		throw std::runtime_error("Illegal option!");
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info, LoggedUser user)
{
	//RoomAdminRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);

	RequestResult result;

	RoomManager& RoomManager = _factoryHandler.getRoomManager();

	try
	{
		CloseRoomResponse response;
		this->_roomManager.deleteRoom(this->_room.getRoomData().id);

		//SUCCESS reponse to login
		response.status = SUCCESS;

		//assign to MenuHandler 
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(user);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}
	catch (const std::exception& e)
	{
		ErrorResponse response;

		//FAILED reponse to login
		response.message = e.what();
		response.id = CLOSE_ROOM_RESPONSE_ID;

		//assign to LoginHandler
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(user);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

	return result;
}

