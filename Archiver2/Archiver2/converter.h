#pragma once
#include <string>

class converter
{
public:
	static std::string bin(int number, int digitCapacity);
	static int binToDec(std::string bin);
};

