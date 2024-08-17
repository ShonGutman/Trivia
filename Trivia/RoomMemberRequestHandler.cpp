#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory& factory, const unsigned int gameRoomID)
    : _factoryHandler(factory), _roomID(gameRoomID)
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
        roomManager.getRoom(_roomID).removeUser(user);

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
        result.newHandler = _factoryHandler.createRoomMemberRequestHandler(_roomID);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(const RequestInfo& info, LoggedUser& user)
{
    RequestResult result;

    RoomManager& roomManager = _factoryHandler.getRoomManager();
    GameManager& gameManager = _factoryHandler.getGameManager();

    try
    {
        GetRoomStatusResponse response;

        response.status = SUCCESS;
        response.players = roomManager.getRoom(_roomID).getAllUsers();
        response.hasGameBegun = roomManager.getRoom(_roomID).getRoomData().isActive;

        //assign to RoomAdminHandler since there were no changes
        
        if (response.hasGameBegun)
        {
            Game& game = gameManager.getGame(_roomID);
            result.newHandler = _factoryHandler.createGameRequestHandler(game);
        }

        else
        {
            result.newHandler = _factoryHandler.createRoomMemberRequestHandler(_roomID);
        }

        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to state room
        response.message = "there is error with room";
        response.id = GET_ROOM_STATE_RESPONSE_ID;

        //assign to menu
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}