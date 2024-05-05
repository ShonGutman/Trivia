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
        || GET_ALL_ROOMS_REQUEST_ID == info.id
        || GET_PLAYERS_IN_ROOM_REQUEST_ID == info.id
        || GET_PERSONAL_SCORE_REQUEST_ID == info.id
        || GET_HIGHEST_SCORE_REQUEST_ID == info.id;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
    if (LOGOUT_REQUEST_ID == info.id)
    {
        return this->logout(info, user);
    }

    else if(JOIN_ROOM_REQUEST_ID == info.id)
    {
        return this->joinRoom(info, user);
    }

    else if (CREATE_ROOM_REQUEST_ID == info.id)
    {
        return this->createRoom(info, user);
    }

    else if (GET_ALL_ROOMS_REQUEST_ID == info.id)
    {
        return this->getAllRooms(info);
    }

    else if (GET_PLAYERS_IN_ROOM_REQUEST_ID == info.id)
    {
        return this->getAllPlayersInRoom(info);
    }

    else if (GET_PERSONAL_SCORE_REQUEST_ID == info.id)
    {
        return this->getPersonalScore(info, user);
    }

    else if (GET_HIGHEST_SCORE_REQUEST_ID == info.id)
    {
        return this->getHighestScores(info);
    }

    else
    {
        throw std::runtime_error("Illegal option!");
    }
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

        //make user none initialized
        user.setToNoneInitialized();
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
    JoinRoomRequest request = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(info.buffer);

    RequestResult result;

    RoomManager& roomManger = _factoryHandler.getRoomManager();

    try
    {
        JoinRoomResponse response;
        roomManger.getRoom(request.roomID).addUser(user);

        //SUCCESS reponse to joinRoom
        response.status = SUCCESS;

        //assign to MenuHandler (for the time being) 
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to joinRoom
        response.message = e.what();
        response.id = JOIN_ROOM_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult MenuRequestHandler::createRoom(const RequestInfo& info, const LoggedUser& user)
{
    CreateRoomRequest request = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(info.buffer);

    RequestResult result;

    RoomManager& roomManger = _factoryHandler.getRoomManager();

    try
    {
        CreateRoomResponse response;

        roomManger.createRoom(user, RoomData(roomManger.getNextRoomId(), request.roomName, request.maxPlayers,
        request.numOfQuestionsInGame, request.timePerQuestion));

        //SUCCESS reponse to createRoom
        response.status = SUCCESS;

        //assign to MenuHandler (for the time being) 
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to createRoom
        response.message = e.what();
        response.id = CREATE_ROOM_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult MenuRequestHandler::getAllRooms(const RequestInfo& info)
{
    RequestResult result;

    RoomManager& roomManager = _factoryHandler.getRoomManager();

    try
    {
        GetAllRoomsResponse response;

        response.rooms = roomManager.getRooms();

        //SUCCESS reponse to getAllrooms
        response.status = SUCCESS;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getAllRooms
        response.message = e.what();
        response.id = GET_ALL_ROOMS_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    
    return result;
}

RequestResult MenuRequestHandler::getAllPlayersInRoom(const RequestInfo& info)
{
    GetPlayersInRoomRequest request = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(info.buffer);

    RequestResult result;

    RoomManager& roomManger = _factoryHandler.getRoomManager();

    try
    {
        GetPlayersInRoomResponse response;

        //retrieve data about the users and the admin
        response.roomAdmin = roomManger.getRoom(request.roomID).getRoomAdmin();
        response.playersInRoom = roomManger.getRoom(request.roomID).getAllUsers();

        //SUCCESS reponse to getAllPlayersInRoom
        response.status = SUCCESS;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getAllPlayersInRoom
        response.message = e.what();
        response.id = GET_PLAYERS_IN_ROOM_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult MenuRequestHandler::getPersonalScore(const RequestInfo& info, const LoggedUser& user)
{
    RequestResult result;

    StatisticsManager& statisticsManager = _factoryHandler.getStatisticsManager();

    try
    {
        GetPersonalStatsResponse response = statisticsManager.getUserStatistics(user.getName());

        //SUCCESS reponse to getPersonalStatsResponse
        response.status = SUCCESS;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getPersonalStatsResponse
        response.message = e.what();
        response.id = GET_PERSONAL_SCORE_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult MenuRequestHandler::getHighestScores(const RequestInfo& info)
{
    RequestResult result;

    StatisticsManager& statisticsManager = _factoryHandler.getStatisticsManager();

    try
    {
        GetHighscoreResponse response = statisticsManager.getHighScore();

        //SUCCESS reponse to getHighscoreResponse
        response.status = SUCCESS;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getHighscoreResponse
        response.message = e.what();
        response.id = GET_HIGHEST_SCORE_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}
