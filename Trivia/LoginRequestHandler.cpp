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

    else if(SIGN_UP_REQUEST_ID == info.id)
    {
        SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(info.buffer);
        SignupResponse response;

        //OK reponse to sign up
        response.status = SUCCESS;

        result.response = JsonResponsePacketSerializer::serializerResponse(response);
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

        //set newHandler to menuHandler!
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

