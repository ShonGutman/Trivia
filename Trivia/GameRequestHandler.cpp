#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& factory, Game& game)
	:_factoryHandler(factory), _game(game)
{
}

bool GameRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return 	LEAVE_GAME_REQUEST_ID == info.id
		|| GET_QUESTION_REQUEST_ID == info.id
		|| SUBMIT_ANSWER_REQUEST_ID == info.id
		|| GET_GAME_RESULT_REQUEST_ID == info.id;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
	return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(const RequestInfo& info, const LoggedUser& user)
{
    RequestResult result;

    try
    {
        LeaveGameResponse response;
        _game.removePlayer(user);

        //SUCCESS reponse to leave game
        response.status = SUCCESS;

        //assign to MenuHandler 
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }

    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to logout
        response.message = e.what();
        response.id = LEAVE_GAME_RESPONSE_ID;

        //if failed stay at game
        result.newHandler = _factoryHandler.createGameRequestHandler(_game);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}
