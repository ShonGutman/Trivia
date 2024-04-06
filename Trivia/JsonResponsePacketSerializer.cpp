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
    Buffer convertResult;

    // Edge case for 0
    if (decNum == 0) {
        convertResult.push_back(0);
        return convertResult;
    }

    // Temporary buffer to store binary digits
    Buffer binaryDigits;

    // Convert decimal to binary
    while (decNum > 0) {
        binaryDigits.push_back(decNum % 2);
        decNum /= 2;
    }

    // Reverse the binary digits to get the correct binary representation
    std::reverse(binaryDigits.begin(), binaryDigits.end());

    // Pad with zeros to make the number of bits a multiple of 8
    while (binaryDigits.size() % SIZE_BYTE != 0) {
        binaryDigits.insert(binaryDigits.begin(), 0);
    }

    // Divide into bytes and put each byte in Buffer
    for (size_t i = 0; i < binaryDigits.size(); i += 8) {
        unsigned char byte = 0;
        for (size_t j = 0; j < SIZE_BYTE; ++j) {
            byte |= (binaryDigits[i + j] << (7 - j));
        }
        convertResult.push_back(byte);
    }

    return convertResult;
}


Buffer JsonResponsePacketSerializer::strToBin(std::string str)
{
    Buffer convertResult;

    // Iterate over each character in the string and convert it to unsigned char
    for (char c : str) {
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
    Buffer sizeBuffer = decToBin(msgSize);
    // Check if the size buffer needs padding or if it's too big
    if (sizeBuffer.size() < SIZE_BYTE_SIZE)
    {
        // Calculate the number of null bytes to add for padding
        int nullAmount = SIZE_BYTE_SIZE - sizeBuffer.size();

        // Add null bytes for padding
        for (int i = 0; i < nullAmount; i++)
        {
            protocolBuffer.push_back('\0');
        }
    }
    else if (sizeBuffer.size() > SIZE_BYTE_SIZE)
    {
        throw ("msg too big");
        return protocolBuffer; // Return empty buffer
    }

    // Add the rest of the size buffer to the protocol buffer
    protocolBuffer.insert(protocolBuffer.end(), sizeBuffer.begin(), sizeBuffer.end());

    // Add message to protocol buffer
    protocolBuffer.insert(protocolBuffer.end(), msg.begin(), msg.end());


    return protocolBuffer;
}
