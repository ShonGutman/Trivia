#pragma once

#include "LoginManager.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory
{
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();

	LoginManager& getLoginManager() const ;

private:
	LoginManager _loginManager;
	IDatabase* _database;
};