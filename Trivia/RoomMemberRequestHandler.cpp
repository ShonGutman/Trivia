#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& factory, Room& gameRoom)
    : _factoryHandler(factory), _room(gameRoom)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& info)
{
    return info.id == LEAVE_ROOM_REQUEST_ID || info.id == GET_ROOM_STATE_REQUEST_ID;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
    switch (info.id)
    {
    case LEAVE_ROOM_REQUEST_ID:
        return leaveRoom(info, user);
        break;
    case GET_ROOM_STATE_REQUEST_ID:
        return getRoomState(info, user);
        break;
    default:
        throw std::runtime_error("Illegal option!");
    }
}

RequestResult RoomMemberRequestHandler::leaveRoom(const RequestInfo& info, LoggedUser& user)
{
    RequestResult result;

    RoomManager& roomManager = _factoryHandler.getRoomManager();

    try
    {
        LeaveRoomResponse response;

        // Remove the user from the room
        _room.removeUser(user);

        //SUCCESS reponse to leave room
        response.status = SUCCESS;

        // Success response to leaving the room
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to closing room
        response.message = e.what();
        response.id = LEAVE_ROOM_RESPONSE_ID;

        //assign to roomAdminHandler
        result.newHandler = _factoryHandler.createRoomMemberRequestHandler(_room);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info, LoggedUser& user)
{
    RequestResult result;

    RoomManager& roomManager = _factoryHandler.getRoomManager();

    try
    {
        GetRoomStatusResponse response;

        response.status = SUCCESS;
        response.players = _room.getAllUsers();
        response.hasGameBegun = _room.getRoomData().isActive;

        //assign to RoomAdminHandler since there were no changes 
        result.newHandler = _factoryHandler.createRoomMemberRequestHandler(_room);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to closing room
        response.message = e.what();
        response.id = GET_ROOM_STATE_RESPONSE_ID;

        //assign to roomAdminHandler
        result.newHandler = _factoryHandler.createRoomMemberRequestHandler(_room);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}