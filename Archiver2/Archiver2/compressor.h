#pragma once
#include <unordered_map>

class compressor
{
public:
	compressor();
	void compress(std::string pathToFile, std::string archiveName);
private:
	std::unordered_map<std::string, int> dictionary;
	int digitCapacity;
	int maxIndex;
	int index;
};

