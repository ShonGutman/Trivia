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

nlohmann::json_abi_v3_11_3::json JsonRequestPacketDeserializer::convertBufferToJson(const Buffer& buffer)
{
    //convert buffer to std::string
    std::string stringBuffer(buffer.begin(), buffer.end());
    //parse std::string into a json object
    return json::parse(stringBuffer);
}
