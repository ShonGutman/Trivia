#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(LoggedUser& user, RequestHandlerFactory& factory)
    :_factoryHandler(factory),
    _user(user)
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
