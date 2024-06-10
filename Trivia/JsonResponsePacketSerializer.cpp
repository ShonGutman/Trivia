#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializerResponse(const ErrorResponse& response)
{
    json jsonErr;

    // Add data to the json object.
    jsonErr[STATUS_KEY] = FAILED;
    jsonErr[MESSAGE_KEY] = response.message;

    return fitBuffToProtocol(jsonErr.dump(), response.id);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const LoginResponse& response)
{
    json jsonLogin;

    // Add data to the json object.
    jsonLogin[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonLogin.dump(), LOGIN_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const SignupResponse& response)
{
    json jsonSignup;

    // Add data to the json object.
    jsonSignup[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonSignup.dump(), SIGN_UP_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const LogoutResponse& response)
{
    json jsonLogout;

    // Add data to the json object.
    jsonLogout[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonLogout.dump(), LOGOUT_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const CloseRoomResponse& response)
{
    json jsonCloseRoom;

    // Add data to the json object.
    jsonCloseRoom[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonCloseRoom.dump(), CLOSE_ROOM_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const StartGameResponse& response)
{
    json jsonStartRoom;

    // Add data to the json object.
    jsonStartRoom[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonStartRoom.dump(), START_GAME_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetRoomStatusResponse& response)
{
    json jsonRoomStatus;

    // Add data to the json object.
    jsonRoomStatus[STATUS_KEY] = response.status;
    jsonRoomStatus[HAS_GAME_BEGUN_KEY] = response.hasGameBegun;
    jsonRoomStatus[PLAYERS_IN_ROOM_KEY] = convertObjectToJson(response.players);

    return fitBuffToProtocol(jsonRoomStatus.dump(), GET_ROOM_STATE_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const LeaveGameResponse& response)
{
    json jsonLeaveGame;

    // Add data to the json object.
    jsonLeaveGame[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonLeaveGame.dump(), LEAVE_GAME_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetAllRoomsResponse& response)
{
    json jsonRoom;

    // Add data to the json object.
    jsonRoom[STATUS_KEY] = response.status;
    jsonRoom[ROOMS_KEY] = convertObjectToJson(response.rooms);

    return fitBuffToProtocol(jsonRoom.dump(), GET_ALL_ROOMS_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetPlayersInRoomResponse& response)
{
    json jsonGetPlayersInRoom;

    jsonGetPlayersInRoom[STATUS_KEY] = response.status;
    jsonGetPlayersInRoom[PLAYERS_IN_ROOM_KEY] = convertObjectToJson(response.playersInRoom);

    return fitBuffToProtocol(jsonGetPlayersInRoom.dump(), GET_PLAYERS_IN_ROOM_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const JoinRoomResponse& response)
{
    json jsonJoinRoom;

    // Add data to the json object.
    jsonJoinRoom[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonJoinRoom.dump(), JOIN_ROOM_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const CreateRoomResponse& response)
{
    json jsonCreateRoom;

    // Add data to the json object.
    jsonCreateRoom[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonCreateRoom.dump(), CREATE_ROOM_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetHighscoreResponse& response)
{
    json jsonHighScore;

    // Add data to the json object.
    jsonHighScore[STATUS_KEY] = response.status;
    jsonHighScore[HIGHSCORES_KEY] = convertObjectToJson(response.highScores).dump();

    return fitBuffToProtocol(jsonHighScore.dump(), GET_HIGHEST_SCORE_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetPersonalStatsResponse& response)
{
    json jsonStats;

    // Add data to the json object.
    jsonStats[STATUS_KEY] = response.status;
    jsonStats[USER_STATISTICS_KEY] = convertObjectToJson(response).dump();

    return fitBuffToProtocol(jsonStats.dump(), GET_PERSONAL_SCORE_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const LeaveRoomResponse& response)
{
    json jsonLeaveRoom;

    // Add data to the json object.
    jsonLeaveRoom[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonLeaveRoom.dump(), LEAVE_ROOM_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetQuestionResponse& response)
{
    json jsonQuestion;

    // Add data to the json object.
    jsonQuestion[STATUS_KEY] = response.status;
    jsonQuestion[QUESTION_KEY] = response.question;
    jsonQuestion[ALL_ANSWERS_KEY] = convertObjectToJson(response.answers);

    return fitBuffToProtocol(jsonQuestion.dump(), GET_QUESTION_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const SubmitAnswerResponse& response)
{
    json jsonsubmitAnswer;

    // Add data to the json object.
    jsonsubmitAnswer[STATUS_KEY] = response.status;
    jsonsubmitAnswer[CORRECT_ANSWER_ID] = response.correctAnswerID;

    return fitBuffToProtocol(jsonsubmitAnswer.dump(), SUBMIT_ANSWER_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const GetGameResultResponse& response)
{
    json jsonGameResults;

    // Add data to the json object.
    jsonGameResults[STATUS_KEY] = response.status;
    jsonGameResults[GAME_RESULTS_KEY] = convertObjectToJson(response.results);

    return fitBuffToProtocol(jsonGameResults.dump(), GET_GAME_RESULTS_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::serializerResponse(const FinishedGameResponse& response)
{
    json jsonFinishedGame;

    //put data into json
    jsonFinishedGame[STATUS_KEY] = response.status;

    return fitBuffToProtocol(jsonFinishedGame.dump(), FINISHED_GAME_RESPONSE_ID);
}

Buffer JsonResponsePacketSerializer::decToBin(const unsigned int decNum)
{
    //credit: https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting

    Buffer convertResult;

    char bytesBuffer[MSG_MAX_SIZE];
    //copy number bytes into char array of MSG_MAX_SIZE bytes
    memcpy(bytesBuffer, (char*)&decNum, MSG_MAX_SIZE);

    //run from end to start since we read number in opposite way
    for (int i = MSG_MAX_SIZE - 1; i >= 0; i--)
    {
        convertResult.push_back(bytesBuffer[i]);
    }
    return convertResult;
}


Buffer JsonResponsePacketSerializer::strToBin(const std::string& str)
{
    Buffer convertResult;

    // Iterate over each character in the string and convert it to unsigned char
    for (char c : str) 
    {
        convertResult.push_back(static_cast<unsigned char>(c));
    }

    return convertResult;
}

Buffer JsonResponsePacketSerializer::fitBuffToProtocol(const std::string& msg, ResponseId code)
{
    // Protocol goes like this :
    // 1 byte - code
    // 4 bytes - size
    // x bytes - msg

    Buffer protocolBuffer;

    // Add code to the protocol buffer
    protocolBuffer.push_back(code);

    unsigned int msgSize = msg.size();

    if (msgSize >= pow(2, MSG_MAX_SIZE * SIZE_BYTE))
    {
        throw ("msg is too big");
        return protocolBuffer; // Return empty buffer
    }

    Buffer sizeBuffer = decToBin(msgSize);


    // Add the rest of the size buffer to the protocol buffer
    protocolBuffer.insert(protocolBuffer.end(), sizeBuffer.begin(), sizeBuffer.end());

    // Add message to protocol buffer
    protocolBuffer.insert(protocolBuffer.end(), msg.begin(), msg.end());


    return protocolBuffer;
}

nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::vector<RoomData>& roomVec)
{
    json convortedJson, currentRoom;

    for (int i = 0; i < roomVec.size(); i++)
    {
        // Adds the data to the currentRoom to the json
        currentRoom[ROOM_ID_KEY] = roomVec[i].id;
        currentRoom[ROOM_NAME_KEY] = roomVec[i].name;
        currentRoom[MAX_PLAYERS_IN_ROOM_KEY] = roomVec[i].maxPlayers;
        currentRoom[NUM_OF_QUESTIONS_IN_GAME_KEY] = roomVec[i].numOfQuestionsInGame;
        currentRoom[TINE_PER_QUESTION_KEY] = roomVec[i].timePerQuestion;
        currentRoom[IS_ACTIVE_KEY] = roomVec[i].isActive;

        // Adds the currentRoom to the json of rooms.
        convortedJson[i] = currentRoom;
    }

    return convortedJson;
}

nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::vector<PlayerResults>& resultVec)
{
    json convortedJson, currentResult;

    for (int i = 0; i < resultVec.size(); i++)
    {
        // Adds the data to the currentResult to the json
        currentResult[USERNAME_KEY] = resultVec[i].username;
        currentResult[NUMBER_OF_RIGHT_ANS_KEY] = resultVec[i].numRightAns;
        currentResult[NUMBER_OF_WRONG_ANS_KEY] = resultVec[i].numWrongAns;
        currentResult[AVG_TIME_FOR_ANS_KEY] = resultVec[i].avgTimeForAns;

        // Adds the currentResult to the json of results.
        convortedJson[i] = currentResult;
    }

    return convortedJson;
}


nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::set<LoggedUser>& LoggedSet)
{
    json convortedJson;

    int i = 0;
    for (auto& it : LoggedSet)
    {
        convortedJson[i++] = it.getName();
    }

    return convortedJson;
}


nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::map<std::string, unsigned int>& scoresMap)
{
    //convert map to json
    // first = name, sec = high score
    return json(scoresMap);
}

nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::map<unsigned int, std::string>& answers)
{
    //convert map to json
    // first = answer id, sec = answer

    nlohmann::json jsonObject = nlohmann::json::object();

    for (const auto& pair : answers) {
        jsonObject[std::to_string(pair.first)] = pair.second;
    }

    return jsonObject;
}

nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const GetPersonalStatsResponse& presonalStatsStruct)
{
    json convortedJson;

    convortedJson[NUMBER_OF_GAMES_KEY] = presonalStatsStruct.numberOfGames;
    convortedJson[NUMBER_OF_RIGHT_ANS_KEY] = presonalStatsStruct.numRightAns;
    convortedJson[NUMBER_OF_WRONG_ANS_KEY] = presonalStatsStruct.numWrongAns;
    convortedJson[AVG_TIME_FOR_ANS_KEY] = presonalStatsStruct.avgTimeForAns;

    return convortedJson;
}
