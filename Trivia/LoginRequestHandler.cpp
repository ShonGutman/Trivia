#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo info)
{
    return info.id == LOGIN_REQUEST_ID || info.id == SIGN_UP_REQUEST_ID;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo info)
{
    //not implemented yet! - THIS FUNCTION REQUEIRES SERI :)
    return RequestResult();
}

