#pragma once
#include <string>
#include <unordered_map>

class decompressor
{
public:
	decompressor();
	void decompress(std::string compressedFIle);
private:
	std::unordered_map<int, std::string> dictionary;
	int digitCapacity;
	int maxIndex;
	int index;
};

