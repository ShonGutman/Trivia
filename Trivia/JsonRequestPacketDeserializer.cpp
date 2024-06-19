#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const Buffer& buffer)
{
    LoginRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.username = jsonMsg[USERNAME_KEY].get<std::string>();
    request.password = jsonMsg[PASSWORD_KEY].get<std::string>();

    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const Buffer& buffer)
{
    SignupRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.username = jsonMsg[USERNAME_KEY].get<std::string>();
    request.password = jsonMsg[PASSWORD_KEY].get<std::string>();
    request.email = jsonMsg[EMAIL_KEY].get<std::string>();
    request.address = jsonMsg[ADDRESS_KEY].get<std::string>();
    request.phoneNumber = jsonMsg[PHONE_NUMBER_KEY].get<std::string>();
    request.birthday = jsonMsg[BIRTHDAY_KEY].get<std::string>();

    return request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const Buffer& buffer)
{
    GetPlayersInRoomRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.roomID = jsonMsg[ROOM_ID_KEY].get<unsigned int>();

    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const Buffer& buffer)
{
    JoinRoomRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.roomID = jsonMsg[ROOM_ID_KEY].get<unsigned int>();

    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const Buffer& buffer)
{
    CreateRoomRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.roomName = jsonMsg[ROOM_NAME_KEY].get<std::string>();
    request.maxPlayers = jsonMsg[MAX_PLAYERS_IN_ROOM_KEY].get<unsigned int>();
    request.numOfQuestionsInGame = jsonMsg[NUM_OF_QUESTIONS_IN_GAME_KEY].get<unsigned int>();
    request.timePerQuestion = jsonMsg[TINE_PER_QUESTION_KEY].get<unsigned int>();

    return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const Buffer& buffer)
{
    SubmitAnswerRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.answerID = jsonMsg[ANSWER_ID_KEY].get<unsigned int>();
    request.timeForAnwser = jsonMsg[ANSWER_RESPONSE_TIME].get<double>();

    return request;
}

sendQuestionRequest JsonRequestPacketDeserializer::deserializeSendQuestionRequest(const Buffer& buffer)
{
    sendQuestionRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.question = jsonMsg[QUESTION_KEY].get<std::string>();
    request.correct = jsonMsg[CORRECT_KEY].get<std::string>();
    request.incorrect1 = jsonMsg[INCORRECT1_KEY].get<std::string>();
    request.incorrect2 = jsonMsg[INCORRECT2_KEY].get<std::string>();
    request.incorrect3 = jsonMsg[INCORRECT3_KEY].get<std::string>();

    return request;
}

ChangePasswordRequest JsonRequestPacketDeserializer::deserializeChangePasswordRequest(const Buffer& buffer)
{
    ChangePasswordRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    // Put data in jsonMsg into request object
    request.username = jsonMsg[USERNAME_KEY].get<std::string>();
    request.newPassword = jsonMsg[NEW_PASSWORD_KEY].get<std::string>();

    return request;
}

nlohmann::json_abi_v3_11_3::json JsonRequestPacketDeserializer::convertBufferToJson(const Buffer& buffer)
{
    //convert buffer to std::string
    std::string stringBuffer(buffer.begin(), buffer.end());
    //parse std::string into a json object
    return json::parse(stringBuffer);
}
