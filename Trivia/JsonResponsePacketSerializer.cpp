#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializerResponse(ErrorResponse response)
{
    Buffer errBuffer;
    json jsonErr;

    // Add data to the json object.
    jsonErr[STATUS] = ERROR_RESPONSE_ID;
    jsonErr[MESSAGE] = response.message;

    errBuffer = fitBuffToProtocol(jsonErr.dump(), ERROR_RESPONSE_ID);

    return errBuffer;

}

Buffer JsonResponsePacketSerializer::serializerResponse(LoginResponse response)
{
    Buffer loginBuffer;
    json jsonLogin;

    // Add data to the json object.
    jsonLogin[STATUS] = LOGIN_RESPONSE_ID;

    loginBuffer = fitBuffToProtocol(jsonLogin.dump(), LOGIN_RESPONSE_ID);

    return loginBuffer;
}

Buffer JsonResponsePacketSerializer::serializerResponse(SignupResponse response)
{
    Buffer SignupBuffer;
    json jsonSignup;

    // Add data to the json object.
    jsonSignup[STATUS] = SIGN_UP_RESPONSE_ID;

    SignupBuffer = fitBuffToProtocol(jsonSignup.dump(), SIGN_UP_RESPONSE_ID);

    return SignupBuffer;
}

Buffer JsonResponsePacketSerializer::decToBin(unsigned int decNum)
{
    //credit: https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting

    Buffer convertResult;

    for (int i = 0; i < MSG_MAX_SIZE; i++)
    {
        // Convert the least significant byte of decNum to a binary representation
        // using std::bitset and push it to the convertResult Buffer
        convertResult.push_back(std::bitset<SIZE_BYTE>(decNum).to_ulong());

        // Right-shift decNum by SIZE_BYTE bits (8 bits for a byte)
        // to extract the next byte for the next iteration
        decNum = decNum >> SIZE_BYTE;
    }
    
    // Since we pushed the bytes in reverse order, we need to reverse
    // the Buffer to get the correct binary representation
    std::reverse(convertResult.begin(), convertResult.end());

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

Buffer JsonResponsePacketSerializer::fitBuffToProtocol(std::string msg, unsigned int code)
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
