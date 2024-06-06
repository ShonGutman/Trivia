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
        || FINISHED_GAME_REQUEST_ID == info.id
		|| GET_GAME_RESULT_REQUEST_ID == info.id;
}

RequestResult GameRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
    switch (info.id)
    {
    case LEAVE_GAME_REQUEST_ID:
        return leaveGame(info, user);
        break;

    case GET_QUESTION_REQUEST_ID:
        return getQuestion(info, user);
        break;

    case SUBMIT_ANSWER_REQUEST_ID:
        return submitAnswer(info, user);
        break;

    case FINISHED_GAME_REQUEST_ID:
        return finishedGame(info, user);
        break;

    case GET_GAME_RESULT_REQUEST_ID:
        break;

    default:
        throw std::runtime_error("Illegal option!");
    }
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

RequestResult GameRequestHandler::getQuestion(const RequestInfo& info, const LoggedUser& user)
{
    RequestResult result;

    try
    {
        GetQuestionResponse response;
        Question userNextQuestion = _game.getNextQuestionForUser(user);

        //put data to reponse
        response.answers = userNextQuestion.getPossibleAnswers();
        response.question = userNextQuestion.getQuestion();
        response.status = SUCCESS;

        //stay at the game
        result.newHandler = _factoryHandler.createGameRequestHandler(_game);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }

    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getQuestion
        response.message = e.what();
        response.id = GET_QUESTION_RESPONSE_ID;

        //if failed stay at game
        result.newHandler = _factoryHandler.createGameRequestHandler(_game);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult GameRequestHandler::submitAnswer(const RequestInfo& info, const LoggedUser& user)
{
    RequestResult result;

    SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);

    try
    {
        SubmitAnswerResponse response;

        //put data to reponse
        response.correctAnswerID = _game.submitAnswer(user, request.answerID, request.timeForAnwser);
        response.status = SUCCESS;

        //stay at the game
        result.newHandler = _factoryHandler.createGameRequestHandler(_game);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }

    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getQuestion
        response.message = e.what();
        response.id = SUBMIT_ANSWER_RESPONSE_ID;

        //if failed move to menu
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult GameRequestHandler::finishedGame(const RequestInfo& info, const LoggedUser& user)
{
    RequestResult result;

    try
    {
        FinishedGameResponse response;

        //put data to reponse
        response.status = SUCCESS;

        //stay at the game
        result.newHandler = _factoryHandler.createGameRequestHandler(_game);
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }

    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to getQuestion
        response.message = e.what();
        response.id = FINISHED_GAME_RESPONSE_ID;

        //if failed move to menu
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}
