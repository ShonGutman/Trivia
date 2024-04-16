#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer& buffer)
{
    LoginRequest request;

    auto jsonMsg = convertBufferToJson(buffer);

    //put data in jsonMsg into request object
    request.username = jsonMsg[USERNAME_KEY].get<std::string>();
    request.password = jsonMsg[PASSWORD_KEY].get<std::string>();

    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(Buffer& buffer)
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

nlohmann::json_abi_v3_11_3::json JsonRequestPacketDeserializer::convertBufferToJson(Buffer& buffer)
{
    //convert buffer to std::string
    std::string stringBuffer(buffer.begin(), buffer.end());
    //parse std::string into a json object
    return json::parse(stringBuffer);
}
