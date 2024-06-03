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

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const unsigned int gameRoomID)
{
    //memory must be deleted
    return new RoomAdminRequestHandler(*this, gameRoomID);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const unsigned int gameRoomID)
{
    //memory must be deleted
    return new RoomMemberRequestHandler(*this, gameRoomID);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Room& room, Game& game)
{
    //memory must be deleted
    return new GameRequestHandler(*this, room, game);
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

GameManager& RequestHandlerFactory::getGameManager()
{
    return this->_gameManager;
}
