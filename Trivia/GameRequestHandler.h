#pragma once

#include <iostream>
#include <string>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

// to avoid circular definition
class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:

	GameRequestHandler(RequestHandlerFactory& factory, const Room& room);

private:

	Game& _game;
	Room& _room;
};
