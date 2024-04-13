#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory)
    :_factoryHandler(factory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo& info)
{
    return info.id == LOGIN_REQUEST_ID || info.id == SIGN_UP_REQUEST_ID;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo& info)
{

    if (LOGIN_REQUEST_ID == info.id)
    {
        return this->login(info);
    }

    else
    {
        return this->signup(info);
    }

}

RequestResult LoginRequestHandler::login(RequestInfo& info)
{
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);

    RequestResult result;

    LoginManager manager = _factoryHandler.getLoginManager();

    try
    {
        LoginResponse response;
        manager.login(request.username, request.password);

        //SUCCESS reponse to login
        response.status = SUCCESS;

        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
        
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to login
        response.message = e.what();
        response.id = LOGIN_RESPONSE_ID;

        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo& info)
{
    SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(info.buffer);

    RequestResult result;

    LoginManager manager = _factoryHandler.getLoginManager();

    try
    {
        LoginResponse response;
        manager.signup(request.username, request.password, request.email);

        //SUCCESS reponse to signup
        response.status = SUCCESS;

        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to login
        response.message = e.what();
        response.id = SIGN_UP_RESPONSE_ID;

        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

