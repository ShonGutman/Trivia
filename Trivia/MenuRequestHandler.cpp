#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& factory)
    :_factoryHandler(factory)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo& info)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& info, LoggedUser& user)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::logout(RequestInfo& info)
{
    return RequestResult();
}
