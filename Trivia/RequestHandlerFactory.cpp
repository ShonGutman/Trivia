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

LoginManager& RequestHandlerFactory::getLoginManager() 
{
    return this->_loginManager;
}
