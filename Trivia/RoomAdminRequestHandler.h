#pragma once

#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

// to avoid circular definition
class RequestHandlerFactory;

class RoomAdminRequestHandler : public IRequestHandler
{
public:
    //CTOR//
    RoomAdminRequestHandler(RequestHandlerFactory& factory, int gameRoomID);

    /**
     * Checks if the given request is relevant to this handler.
     *
     * This function checks if the provided request, represented by a RequestInfo object,
     * is relevant to the RoomAdminRequestHandler. It returns true if the request is relevant,
     * and false otherwise.
     *
     * @param info The RequestInfo object containing request details.
     * @return true if the request is relevant, false otherwise.
     */
    bool isRequestRelevant(const RequestInfo& info) override;

    /**
     * Handles the given request.
     *
     * This function handles the provided request, represented by a RequestInfo object,
     * from the given LoggedUser. It processes the request and returns a RequestResult object
     * containing the result of handling the request.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:

    int _roomID; ///<  the ID of the Room object.
    RequestHandlerFactory& _factoryHandler; ///< Reference to the RequestHandlerFactory.

    /**
     * Handles the request to close the room.
     *
     * This function handles the request to close the room, represented by a RequestInfo object,
     * from the given LoggedUser. It processes the request and returns a RequestResult object
     * containing the result of handling the request.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult closeRoom(const RequestInfo& info, LoggedUser& user);

    /**
     * Handles the request to start the game.
     *
     * This function handles the request to start the game, represented by a RequestInfo object,
     * from the given LoggedUser. It processes the request and returns a RequestResult object
     * containing the result of handling the request.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult startGame(const RequestInfo& info, LoggedUser& user);

    /**
     * Handles the request to get the state of the room.
     *
     * This function handles the request to get the state of the room, represented by a RequestInfo object,
     * from the given LoggedUser. It processes the request and returns a RequestResult object
     * containing the result of handling the request.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult getRoomState(const RequestInfo& info, LoggedUser& user);
};
