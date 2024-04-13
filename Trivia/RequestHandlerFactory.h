#pragma once

#include "LoginManager.h"
#include "IDatabase.h"
#include "LoginRequestHandler.h"

// to avoid circular definition
class LoginRequestHandler;

class RequestHandlerFactory
{
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();

	LoginManager& getLoginManager() const ;

private:
	LoginManager _loginManager;
	IDatabase* _database;
};