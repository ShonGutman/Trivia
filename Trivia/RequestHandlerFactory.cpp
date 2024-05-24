#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    : _database(database),
    _loginManager(LoginManager::get(database)),
    _roomManager(RoomManager::get()),
    _statisticsManager(StatisticsManager::get(database))
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

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(Room& gameRoom)
{
    //memory must be deleted
    return new RoomAdminRequestHandler(*this, gameRoom);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(Room& gameRoom)
{
    //memory must be deleted
    return new RoomMemberRequestHandler(*this, gameRoom);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return this->_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
    return this->_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
    return this->_statisticsManager;
}