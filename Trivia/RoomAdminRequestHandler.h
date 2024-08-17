#pragma once

#include <thread>
#include <chrono>
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
    RoomAdminRequestHandler(RequestHandlerFactory& factory, const unsigned int gameRoomID);

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

    unsigned int _roomID; ///<  the ID of the Room object.
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

    /*
    * Handles the request to start a game in the room.
    * It activates the room, creates a game, and initiates a thread to delete the room and game data after the game finishes.
    *
    * @param info The request information.
    * @param user The logged-in user initiating the request.
    * @return RequestResult containing the response and the next handler to be used.
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

    /*
    * Deletes data associated with a room and game after a specified time period.
    * This function is intended to be executed in a separate thread.
    * It sleeps for the specified time plus a safety buffer of 10 seconds before deleting the room and game data.
    *
    * @param id The ID of the room and game to be deleted.
    * @param timeInSeconds The time period after which the data will be deleted.
    */
    static void deleteDataThread(RequestHandlerFactory& factoryHandler, const unsigned int id, const unsigned int timeInSeconds);
};
