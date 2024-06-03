#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler(RequestHandlerFactory& factory, Room& room, Game& game)
	:_factoryHandler(factory), _room(room), _game(game)
{
}
