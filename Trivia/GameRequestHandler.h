#pragma once

#include <iostream>
#include <string>
#include <condition_variable>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

// to avoid circular definition
class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:

	//CTOR//
	GameRequestHandler(RequestHandlerFactory& factory, Game& game);

	bool isRequestRelevant(const RequestInfo& info) override;

	RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:

	RequestResult leaveGame(const RequestInfo& info, const LoggedUser& user);

	RequestResult getQuestion(const RequestInfo& info, const LoggedUser& user);

	RequestResult submitAnswer(const RequestInfo& info, const LoggedUser& user);

	RequestResult finishedGame(const RequestInfo& info, const LoggedUser& user);

	Game& _game;
	RequestHandlerFactory& _factoryHandler;
};
