#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : _database(database),
    _loginManager(LoginManager::get(database)),
    _roomManager(RoomManager::get())
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    //memory must be deleted
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    //memory must be deleted
    return new MenuRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return this->_roomManager;
}
