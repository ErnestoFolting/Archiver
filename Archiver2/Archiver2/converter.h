#pragma once
#include <string>

class converter
{
public:
	static std::string decimalToBinary(int number, int digitCapacity);
	static int binaryToDecimal(std::string binary);
};

