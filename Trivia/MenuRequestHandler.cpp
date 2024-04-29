#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory& factory)
    :_factoryHandler(factory)
{
}

bool MenuRequestHandler::isRequestRelevant(const RequestInfo& info)
{
    return false;
}

RequestResult MenuRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{
    return RequestResult();
}

RequestResult MenuRequestHandler::logout(const RequestInfo& info, LoggedUser& user)
{
    RequestResult result;

    LoginManager& manager = _factoryHandler.getLoginManager();

	try
	{
		LogoutResponse response;
		manager.logout(user.getName());

        //SUCCESS reponse to logout
        response.status = SUCCESS;

        //assign to LoginHandler 
        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

        //make user initialized
        user.setToInitialized();
	}

	catch (const std::exception& e)
	{
        ErrorResponse response;

        //FAILED reponse to logout
        response.message = e.what();
        response.id = LOGOUT_RESPONSE_ID;

        //assign to MenuHandler
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
	}

    return result;
}
