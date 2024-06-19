#include "LoginRequestHandler.h"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& factory)
    :_factoryHandler(factory)
{
}

bool LoginRequestHandler::isRequestRelevant(const RequestInfo& info)
{
    return info.id == LOGIN_REQUEST_ID || info.id == SIGN_UP_REQUEST_ID || info.id == CHANGE_PASSWORD_REQUEST_ID;
}

RequestResult LoginRequestHandler::handleRequest(const RequestInfo& info, LoggedUser& user)
{

    if (LOGIN_REQUEST_ID == info.id)
    {
        return this->login(info, user);
    }

    else if(SIGN_UP_REQUEST_ID == info.id)
    {
        return this->signup(info, user);
    }

    else if (CHANGE_PASSWORD_REQUEST_ID == info.id)
    {
        return this->changePassword(info, user);
    }

    else
    {
        throw std::runtime_error("Illegal option!");
    }

}

RequestResult LoginRequestHandler::login(const RequestInfo& info, LoggedUser& user)
{
    LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(info.buffer);

    RequestResult result;

    LoginManager& loginManager = _factoryHandler.getLoginManager();

    try
    {
        LoginResponse response;
        loginManager.login(request.username, request.password);

        //SUCCESS reponse to login
        response.status = SUCCESS;

        //assign to MenuHandler 
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

        //insert the username into loggedUser object
        user.setName(request.username);
        
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to login
        response.message = e.what();
        response.id = LOGIN_RESPONSE_ID;

        //assign to LoginHandler
        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& info, LoggedUser& user)
{
    SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(info.buffer);

    RequestResult result;

    LoginManager& loginManager = _factoryHandler.getLoginManager();

    try
    {
        SignupResponse response;
        loginManager.signup(request.username, request.password, request.email, request.address, request.phoneNumber, request.birthday);

        //SUCCESS reponse to signup
        response.status = SUCCESS;

        //assign to MenuHandler 
        result.newHandler = _factoryHandler.createMenuRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);

        //insert the username into loggedUser object
        user.setName(request.username);

    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        //FAILED reponse to login
        response.message = e.what();
        response.id = SIGN_UP_RESPONSE_ID;

        //assign to LoginHandler 
        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}

RequestResult LoginRequestHandler::changePassword(const RequestInfo& info, LoggedUser& user)
{
    ChangePasswordRequest request = JsonRequestPacketDeserializer::deserializeChangePasswordRequest(info.buffer);

    RequestResult result;

    LoginManager& loginManager = _factoryHandler.getLoginManager();

    try
    {
        ChangePasswordResponse response;
        loginManager.changePassword(request.username, request.currentPassword, request.newPassword);

        // SUCCESS response to change password
        response.status = SUCCESS;

        // Assign to LoginHandler
        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }
    catch (const std::exception& e)
    {
        ErrorResponse response;

        // FAILED response to change password
        response.message = e.what();
        response.id = CHANGE_PASSWORD_RESPONSE_ID;

        // Assign to LoginHandler
        result.newHandler = _factoryHandler.createLoginRequestHandler();
        result.response = JsonResponsePacketSerializer::serializerResponse(response);
    }

    return result;
}
