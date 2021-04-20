#include "compressor.h"
#include "converter.h"
#include "bytesWriter.h"
#include <string>
#include <iostream>
#include <unordered_map>
#include <fstream>
#include "view.h"

using namespace std;

compressor::compressor():
digitCapacity(9), maxIndex(512), index(256)
{
	for(int i=0;i<=255;i++)
	{
		dictionary.insert(make_pair(string(1, static_cast<char>(i)), i));
	}
}

void compressor::compress(string fileName, string archiveName)
{	
	ifstream inFile(fileName, ios::binary);
	if (!inFile) {
		view::canNotOpenToCompress();
	}
	else {
		view::compressStarted(fileName);
		char byte;
		inFile.read(&byte, sizeof(char));
		string currentlyRecognised = string(1, static_cast<char>(byte));
		vector<string> stringBinaryEncoding;

		while (inFile.read(&byte, sizeof(char)))
		{
			if (dictionary.contains(currentlyRecognised + string(1, static_cast<char>(byte))))
			{
				currentlyRecognised += string(1, static_cast<char>(byte));
			}
			else
			{
				if (index == maxIndex)
				{
					digitCapacity++;
					maxIndex *= 2;
				}
				stringBinaryEncoding.push_back(converter::decimalToBinary(dictionary.at(currentlyRecognised), digitCapacity));
				dictionary.insert(make_pair(currentlyRecognised + string(1, static_cast<char>(byte)), index));
				index++;
				currentlyRecognised = string(1, static_cast<char>(byte));
			}
		}
		if (index == maxIndex)
		{
			digitCapacity++;
			maxIndex *= 2;
		}
		stringBinaryEncoding.push_back(converter::decimalToBinary(dictionary.at(currentlyRecognised), digitCapacity));
		inFile.close();
		bytesWriter::writeCompressedBytes(stringBinaryEncoding, archiveName, fileName);
	}
	
}
