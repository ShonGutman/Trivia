#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializerResponse(ErrorResponse response)
{
    Buffer errBuffer;
    json jsonErr;

    // Add data to the json object.
    jsonErr[STATUS_KEY] = FAILED;
    jsonErr[MESSAGE_KEY] = response.message;

    errBuffer = fitBuffToProtocol(jsonErr.dump(), ERROR_RESPONSE_ID);

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
