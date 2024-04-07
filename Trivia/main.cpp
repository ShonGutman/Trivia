#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include "JsonResponsePacketSerializer.h"
#include "Responses.h"
#include <iostream>
#include <exception>


void printBuffer(const Buffer& buffer) {
    std::cout << "Buffer content:" << std::endl;
    std::cout << "---------------" << std::endl;

    // Iterate through each element of the buffer
    for (size_t i = 0; i < buffer.size(); ++i) {
        // Print the current byte in hexadecimal format
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buffer[i]);

        //// Add a space between each byte for readability
        //if (i != buffer.size() - 1) {
        //    std::cout << " ";
        //}

        //// Print a newline after every 16 bytes for better formatting
        //if ((i + 1) % 16 == 0) {
        //    std::cout << std::endl;
        //}
    }

    // Print a newline at the end
    std::cout << std::endl;
    std::cout << std::endl;
}

int main() {
    try {
        // Test serializerResponse(ErrorResponse)
        ErrorResponse errResponse;
        errResponse.message = "Error message";
        Buffer errBuffer = JsonResponsePacketSerializer::serializerResponse(errResponse);
        std::cout << "Error response buffer size: " << errBuffer.size() << std::endl;
        printBuffer(errBuffer); // Print the contents of errBuffer

        // Test serializerResponse(LoginResponse)
        LoginResponse logResponse;
        logResponse.status = LOGIN_RESPONSE_ID;
        Buffer loginBuffer = JsonResponsePacketSerializer::serializerResponse(logResponse);
        std::cout << "Login response buffer size: " << loginBuffer.size() << std::endl;
        printBuffer(loginBuffer); // Print the contents of loginBuffer

        // Test serializerResponse(SignupResponse)
        SignupResponse signupResponse;
        signupResponse.status = SIGN_UP_RESPONSE_ID;
        Buffer signupBuffer = JsonResponsePacketSerializer::serializerResponse(signupResponse);
        std::cout << "Signup response buffer size: " << signupBuffer.size() << std::endl;
        printBuffer(signupBuffer); // Print the contents of signupBuffer

        //// Test decToBin(unsigned int)
        //unsigned int num = 123456;
        //Buffer binBuffer = JsonResponsePacketSerializer::decToBin(num);
        //std::cout << "Binary buffer size for " << num << ": " << binBuffer.size() << std::endl;
        //printBuffer(binBuffer); // Print the contents of binBuffer

        //// Test strToBin(std::string)
        //std::string str = "HI!";
        //Buffer strBuffer = JsonResponsePacketSerializer::strToBin(str);
        //std::cout << "String buffer size for '" << str << "': " << strBuffer.size() << std::endl;
        //printBuffer(strBuffer); // Print the contents of strBuffer

        //// Test fitBuffToProtocol(json, unsigned int)
        //json msg = { {"key1", "value1"}, {"key2", "value2"} };
        //unsigned int code = 123;
        //Buffer protocolBuffer = JsonResponsePacketSerializer::fitBuffToProtocol(msg.dump(), code);
        //std::cout << "Protocol buffer size: " << protocolBuffer.size() << std::endl;
        //printBuffer(protocolBuffer); // Print the contents of protocolBuffer

        return 0;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}