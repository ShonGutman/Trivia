#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& factory)
    :_factoryHandler(factory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info)
{
    return LOGOUT_REQUEST_ID == info.id 
        || JOIN_ROOM_REQUEST_ID == info.id
        || CREATE_ROOM_REQUEST_ID == info.id
        || CREATE_ROOM_REQUEST_ID == info.id
        || GET_ALL_ROOMS_REQUEST_ID == info.id
        || GET_PLAYERS_IN_ROOM_REQUEST_ID == info.id
        || GET_PERSONAL_SCORE_REQUEST_ID == info.id
        || GET_HIGHEST_SCORE_REQUEST_ID == info.id;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::logout(const RequestInfo& info, LoggedUser& user)
{
    RequestResult result;

    LoginManager& loginManager = _factoryHandler.getLoginManager();

	try
	{
		LogoutResponse response;
		loginManager.logout(user.getName());

        //SUCCESS reponse to logout
        response.status = SUCCESS;

        //assign to LoginHandler 
        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

        //make user initialized
        user.setToInitialized();
	}

	catch (const std::exception& e)
	{
        ErrorResponse response;

        //FAILED reponse to logout
        response.message = e.what();
        response.id = LOGOUT_RESPONSE_ID;

        //if logout falied we want to remove that user, there should be no reason for logout to fail
        //unless user somehow skipped to menu
        result.newHandler = nullptr;
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

    return result;
}

RequestResult MenuRequestHandler::joinRoom(const RequestInfo& info, const LoggedUser& user)
{
    RequestResult result;

    RoomManager& roomManger = _factoryHandler.getRoomManager();
}
