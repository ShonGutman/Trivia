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
    /**
     * Constructs a new RoomAdminRequestHandler.
     *
     * @param factory Reference to the RequestHandlerFactory.
     * @param gameRoom Reference to the Room object.
     */
    RoomAdminRequestHandler(RequestHandlerFactory& factory, Room& gameRoom);

    /**
     * Checks if the given request is relevant to this handler.
     *
     * @param info The RequestInfo object containing request details.
     * @return true if the request is relevant, false otherwise.
     */
    bool isRequestRelevant(const RequestInfo& info) override;

    /**
     * Handles the given request.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult handleRequest(const RequestInfo& info, LoggedUser& user) override;

private:
    Room& _room; ///< Reference to the Room object.
    RequestHandlerFactory& _factoryHandler; ///< Reference to the RequestHandlerFactory.

    /**
     * Handles the request to close the room.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult closeRoom(const RequestInfo& info, LoggedUser& user);

    /**
     * Handles the request to start the game.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult startGame(const RequestInfo& info, LoggedUser& user);

    /**
     * Handles the request to get the state of the room.
     *
     * @param info The RequestInfo object containing request details.
     * @param user The LoggedUser object representing the user making the request.
     * @return A RequestResult object containing the result of handling the request.
     */
    RequestResult getRoomState(const RequestInfo& info, LoggedUser& user);
};
