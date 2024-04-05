#include "JsonResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::decToBin(unsigned int decNum)
{
    Buffer convertResult;

    // Edge case for 0
    if (decNum == 0) {
        convertResult.push_back(0);
        return convertResult;
    }

    // Temporary buffer to store binary digits
    std::vector<int> binaryDigits;

    // Convert decimal to binary
    while (decNum > 0) {
        binaryDigits.push_back(decNum % 2);
        decNum /= 2;
    }

    // Reverse the binary digits to get the correct binary representation
    for (int i = binaryDigits.size() - 1; i >= 0; --i) {
        convertResult.push_back(binaryDigits[i]);
    }

    return convertResult;
}
