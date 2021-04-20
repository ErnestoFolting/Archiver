#include "byteCounter.h"

long long int byteCounter::getSizeOfFile(std::vector<std::string> tempVector)
{
    long long int size = 0;
    for (int i = 0; i < tempVector.size(); i++) {
        for (int j = 0; j < tempVector[i].length(); j++) {
            size++;
        }
    }
    while (size % 8) {
        size++;
    }
    size /= 8;
    return size;
}
