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
    request.email = jsonMsg[EMAIL_LEY].get<std::string>();

    return request;
}

int JsonRequestPacketDeserializer::binToDec(Buffer& buffer)
{
    char bytesBuffer[MSG_MAX_SIZE];


    //run from end to start since we read number in opposite way
    for (int i = 0; i < MSG_MAX_SIZE; i++)
    {
        bytesBuffer[i] = buffer[MSG_MAX_SIZE - 1 - i];
    }

    int decNum = 0;
    memcpy(&decNum, (int*)bytesBuffer, MSG_MAX_SIZE);
    return decNum;
}

nlohmann::json_abi_v3_11_3::json JsonRequestPacketDeserializer::convertBufferToJson(Buffer& buffer)
{
    //convert buffer to std::string
    std::string stringBuffer(buffer.begin(), buffer.end());
    //parse std::string into a json object
    return json::parse(stringBuffer);
}
