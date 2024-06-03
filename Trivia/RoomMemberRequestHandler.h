#pragma once

#include "Room.h"
#include "RoomManager.h"
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"

// to avoid circular definition
class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler
{
public:
    //CTOR//
	RoomMemberRequestHandler(RequestHandlerFactory& factory, const unsigned int gameRoomID);

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
    int _roomID; ///< ID to the Room object.
    RequestHandlerFactory& _factoryHandler; ///< Reference to the RequestHandlerFactory.

    /**
     * Handles the request to leave the room.
     *
     * This function processes the request from a user to leave the room specified in the RequestInfo object.
     * It updates the state of the room accordingly, removing the user from the room's list of participants.
     * If the user was the last participant in the room, the room is deleted.
     *
     * @param info The RequestInfo object containing details of the request, including the room ID.
     * @param user The LoggedUser object representing the user who is leaving the room.
     * @return A RequestResult object indicating the result of the operation:
     */
    RequestResult leaveRoom(const RequestInfo& info, LoggedUser& user);

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