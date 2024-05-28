#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory& factory, int gameRoomID)
	:_factoryHandler(factory), _roomID(gameRoomID)
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
		return startGame(info, user);
		break;
	case CLOSE_ROOM_REQUEST_ID:
		return closeRoom(info, user);
		break;
	case GET_ROOM_STATE_REQUEST_ID:
		return getRoomState(info, user);
		break;

	default:
		throw std::runtime_error("Illegal option!");
	}
}

RequestResult RoomAdminRequestHandler::closeRoom(const RequestInfo& info, LoggedUser& user)
{
	RequestResult result;

	RoomManager& roomManager = _factoryHandler.getRoomManager();

	try
	{
		CloseRoomResponse response;
		roomManager.deleteRoom(_roomID);

		//SUCCESS reponse to close room
		response.status = SUCCESS;

		//assign to MenuHandler 
		result.newHandler = _factoryHandler.createMenuRequestHandler();
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}
	catch (const std::exception& e)
	{
		ErrorResponse response;

		//FAILED reponse to closing room
		response.message = e.what();
		response.id = CLOSE_ROOM_RESPONSE_ID;

		//assign to roomAdminHandler
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(_roomID);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

	return result;
}

RequestResult RoomAdminRequestHandler::startGame(const RequestInfo& info, LoggedUser& user)
{
	RequestResult result;

	RoomManager& roomManager = _factoryHandler.getRoomManager();

	try
	{
		StartGameResponse response;
		roomManager.getRoom(_roomID).makeRoomActive();

		//SUCCESS reponse to opening room
		response.status = SUCCESS;

		//assign to RoomAdminHandler in the meanwhile CHANGE TO GAME HANDLER IN THE FUTURE
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(_roomID);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}
	catch (const std::exception& e)
	{
		ErrorResponse response;

		//FAILED reponse to closing room
		response.message = e.what();
		response.id = CLOSE_ROOM_RESPONSE_ID;

		//assign to menu since the creation did not succsed
		result.newHandler = _factoryHandler.createMenuRequestHandler();
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(const RequestInfo& info, LoggedUser& user)
{
	RequestResult result;

	RoomManager& roomManager = _factoryHandler.getRoomManager();

	try
	{
		GetRoomStatusResponse response;

		//SUCCESS reponse to room status
		response.status = SUCCESS;
		response.players = roomManager.getRoom(_roomID).getAllUsers();
		response.hasGameBegun = roomManager.getRoom(_roomID).getRoomData().isActive;

		//assign to RoomAdminHandler since there were no changes 
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(_roomID);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}
	catch (const std::exception& e)
	{
		ErrorResponse response;

		//FAILED reponse to room status
		response.message = e.what();
		response.id = GET_ROOM_STATE_RESPONSE_ID;

		//assign to RoomAdminHandler since there were no changes 
		result.newHandler = _factoryHandler.createRoomAdminRequestHandler(_roomID);
		result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

	return result;
}

