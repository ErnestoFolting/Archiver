#include "byteCounter.h"

long long int byteCounter::getSizeOfFile(std::vector<std::string> fileBits)
{
    long long int size = 0;
    for (int i = 0; i < fileBits.size(); i++) {
        for (int j = 0; j < fileBits[i].length(); j++) {
            size++;
        }
    }
    while (size % 8) {
        size++;
    }
    size /= 8;
    return size;
}
