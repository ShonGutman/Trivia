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

	/*
	* Handles the request for a user to leave the game.
	* It removes the player from the game and notifies all threads if the game has finished.
	*
	* @param info The request information.
	* @param user The logged-in user leaving the game.
	* @return RequestResult containing the response and the next handler to be used.
	*/
	RequestResult leaveGame(const RequestInfo& info, const LoggedUser& user);

	/*
	* Handles the request to get the next question for the user in the game.
	* It retrieves the next question for the user and constructs a response containing the question and possible answers.
	*
	* @param info The request information.
	* @param user The logged-in user requesting the next question.
	* @return RequestResult containing the response and the next handler to be used.
	*/
	RequestResult getQuestion(const RequestInfo& info, const LoggedUser& user);

	/*
	* Handles the request to submit an answer to the current question in the game.
	* It processes the submitted answer and constructs a response indicating whether the answer was correct.
	*
	* @param info The request information.
	* @param user The logged-in user submitting the answer.
	* @return RequestResult containing the response and the next handler to be used.
	*/
	RequestResult submitAnswer(const RequestInfo& info, const LoggedUser& user);

	/*
	* Handles the request to indicate that the user has finished the game.
	* It updates the game state accordingly and notifies all threads if the game has finished.
	*
	* @param info The request information.
	* @param user The logged-in user indicating the end of the game.
	* @return RequestResult containing the response and the next handler to be used.
	*/
	RequestResult finishedGame(const RequestInfo& info, const LoggedUser& user);

	/*
	* Handles the request to retrieve the results of the finished game.
	* It waits until all players have finished or left the game, then retrieves and constructs a response containing the game results.
	*
	* @param info The request information.
	* @return RequestResult containing the response and the next handler to be used.
	*/
	RequestResult getResults(const RequestInfo& info);

	Game& _game;
	RequestHandlerFactory& _factoryHandler;
};
