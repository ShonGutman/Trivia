#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& factory)
    :_factoryHandler(factory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::logout(const RequestInfo& info)
{
    return RequestResult();
}
