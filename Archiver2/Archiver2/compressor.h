#pragma once
#include <unordered_map>

class compressor
{
public:
	compressor(std::string pathToFile);
	void compress();
private:
	std::unordered_map<std::string, int> dictionary;
	std::string pathToFile;
	int digitCapacity;
	int maxIndex;
	int index;
};

