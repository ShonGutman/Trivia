#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo& info)
{
    return info.id == LOGIN_REQUEST_ID || info.id == SIGN_UP_REQUEST_ID;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo& info)
{
    RequestResult result;
    if (LOGIN_REQUEST_ID == info.id)
    {
        LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);
        LoginResponse response;

        //OK reponse to login
        response.status = SUCCESS;

        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    else if(SIGN_UP_REQUEST_ID == info.id)
    {
        SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(info.buffer);
        SignupResponse response;

        //OK reponse to sign up
        response.status = SUCCESS;

        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    result.newHandler = this;
    return result;
}

