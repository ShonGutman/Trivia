#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializerResponse(ErrorResponse errResponse)
{
    Buffer errBuffer;
    json jsonErr;

    ResponseId responseID = ERROR_RESPONSE_ID;

    // Add data to the json object.
    jsonErr[STATUS] = responseID;
    jsonErr[MESSAGE] = errResponse.message;

    errBuffer = fitBuffToProtocol(jsonErr.dump(), responseID);

    return errBuffer;

}

Buffer JsonResponsePacketSerializer::serializerResponse(LoginResponse LogResponse)
{
    Buffer loginBuffer;
    json jsonLogin;

    ResponseId responseID = LOGIN_RESPONSE_ID;

    // Add data to the json object.
    jsonLogin[STATUS] = responseID;

    loginBuffer = fitBuffToProtocol(jsonLogin.dump(), responseID);

    return loginBuffer;
}

Buffer JsonResponsePacketSerializer::serializerResponse(SignupResponse)
{
    Buffer SignupBuffer;
    json jsonSignup;

    ResponseId responseID = SIGN_UP_RESPONSE_ID;

    // Add data to the json object.
    jsonSignup[STATUS] = responseID;

    SignupBuffer = fitBuffToProtocol(jsonSignup.dump(), responseID);

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
    std::vector<unsigned char> binaryDigits;

    // Convert decimal to binary
    while (decNum > 0) {
        binaryDigits.push_back(decNum % 2);
        decNum /= 2;
    }

    // Reverse the binary digits to get the correct binary representation
    std::reverse(binaryDigits.begin(), binaryDigits.end());

    // Pad with zeros to make the number of bits a multiple of 8
    while (binaryDigits.size() % 8 != 0) {
        binaryDigits.insert(binaryDigits.begin(), 0);
    }

    // Divide into bytes and put each byte in Buffer
    for (size_t i = 0; i < binaryDigits.size(); i += 8) {
        unsigned char byte = 0;
        for (size_t j = 0; j < 8; ++j) {
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

    protocolBuffer.push_back(code);

    unsigned int msgSize = msg.size();
    Buffer sizeBuffer = decToBin(msgSize);
    for (const auto& byte : sizeBuffer)
    {
        protocolBuffer.push_back(byte);
    }

    // Add message to protocol buffer
    for (unsigned char byte : msg) {
        protocolBuffer.push_back(byte);
    }

    return protocolBuffer;
}
