#include "RequestHandlerFactory.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database)
    :_database(database)
{
    _loginManager = LoginManager(database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    //memory must be deleted
    return new LoginRequestHandler(*this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
    //memory must be deleted
    //for the time being it is empty.
    return new MenuRequestHandler();
}

LoginManager& RequestHandlerFactory::getLoginManager() 
{
    return this->_loginManager;
}
