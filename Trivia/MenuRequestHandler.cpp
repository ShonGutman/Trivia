#include "MenuRequestHandler.h"

bool MenuRequestHandler::isRequestRelevant(RequestInfo& info)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& info, LoggedUser& user)
{
    return RequestResult();
}
