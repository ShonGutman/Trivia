#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializerResponse(ErrorResponse response)
{
    Buffer errBuffer;
    json jsonErr;

    // Add data to the json object.
    jsonErr[STATUS_KEY] = FAILED;
    jsonErr[MESSAGE_KEY] = response.message;

    errBuffer = fitBuffToProtocol(jsonErr.dump(), response.id);

    return errBuffer;

}

Buffer JsonResponsePacketSerializer::serializerResponse(LoginResponse response)
{
    Buffer loginBuffer;
    json jsonLogin;

    // Add data to the json object.
    jsonLogin[STATUS_KEY] = response.status;

    loginBuffer = fitBuffToProtocol(jsonLogin.dump(), LOGIN_RESPONSE_ID);

    return loginBuffer;
}

Buffer JsonResponsePacketSerializer::serializerResponse(SignupResponse response)
{
    Buffer SignupBuffer;
    json jsonSignup;

    // Add data to the json object.
    jsonSignup[STATUS_KEY] = response.status;

    SignupBuffer = fitBuffToProtocol(jsonSignup.dump(), SIGN_UP_RESPONSE_ID);

    return SignupBuffer;
}

Buffer JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse response)
{
    Buffer logoutBuffer;
    json jsonLogout;

    // Add data to the json object.
    jsonLogout[STATUS_KEY] = response.status;

    logoutBuffer = fitBuffToProtocol(jsonLogout.dump(), LEAVE_ROOM_RESPONSE_ID);

    return logoutBuffer;
}

Buffer JsonResponsePacketSerializer::serializeGetRoomResponse(GetRoomsResponse response)
{
    Buffer roomBuffer;
    json jsonRoom;

    // Add data to the json object.
    jsonRoom[STATUS_KEY] = response.status;
    jsonRoom[ROOMS_KEY] = convertObjectToJson(response.rooms);

}

Buffer JsonResponsePacketSerializer::serializeJoinRoomResponse(JoinRoomResponse response)
{
    Buffer joinRoomBuffer;
    json jsonJoinRoom;

    // Add data to the json object.
    jsonJoinRoom[STATUS_KEY] = response.status;

    joinRoomBuffer = fitBuffToProtocol(jsonJoinRoom.dump(), JOIN_ROOM_RESPONSE_ID);

    return joinRoomBuffer;
}

Buffer JsonResponsePacketSerializer::serializeCreateRoomResponse(CreateRoomResponse response)
{
    Buffer createRoomBuffer;
    json jsonCreateRoom;

    // Add data to the json object.
    jsonCreateRoom[STATUS_KEY] = response.status;

    createRoomBuffer = fitBuffToProtocol(jsonCreateRoom.dump(), CREATE_ROOM_RESPONSE_ID);

    return createRoomBuffer;
}

Buffer JsonResponsePacketSerializer::decToBin(unsigned int decNum)
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


Buffer JsonResponsePacketSerializer::strToBin(std::string str)
{
    Buffer convertResult;

    // Iterate over each character in the string and convert it to unsigned char
    for (char c : str) 
    {
        convertResult.push_back(static_cast<unsigned char>(c));
    }

    return convertResult;
}

Buffer JsonResponsePacketSerializer::fitBuffToProtocol(std::string msg, ResponseId code)
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

nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::vector<const RoomData>& roomVec)
{
    json convortedJson, currentRoom;

    for (int i = 0; i < roomVec.size(); i++)
    {
        // Adds the data to the currentRoom to the json
        currentRoom[ID] = roomVec[i].id;
        currentRoom[NAME] = roomVec[i].name;
        currentRoom[MAX_PLAYERS] = roomVec[i].maxPlayers;
        currentRoom[NUM_OF_QUESTION_IN_GAME] = roomVec[i].numOfQuestionsInGame;
        currentRoom[TIME_PER_QUESTION] = roomVec[i].timePerQuestion;
        currentRoom[IS_ACTIVE] = roomVec[i].isActive;

        // Adds the currentRoom to the json of rooms.
        convortedJson[i] = currentRoom.dump();
    }

    return convortedJson;
}


nlohmann::json_abi_v3_11_3::json JsonResponsePacketSerializer::convertObjectToJson(const std::vector<const std::string>& stringVec)
{
    json convortedJson;

    for (int i = 0; i < stringVec.size(); i++)
    {
        convortedJson[i] = stringVec[i];
    }

    return convortedJson;
}