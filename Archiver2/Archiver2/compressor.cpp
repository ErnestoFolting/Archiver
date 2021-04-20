#include "compressor.h"
#include "converter.h"
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

compressor::compressor(std::string pathToFile):
digitCapacity(9), maxIndex(512), index(256), pathToFile(pathToFile)
{
	for(int i=0;i<=255;i++)
	{
		dictionary.insert(make_pair(string(1, static_cast<char>(i)), i));
	}
}

void compressor::compress()
{	
	ifstream inFile(pathToFile, ios::binary);
	char byte;
	inFile.read(&byte, sizeof(char));
	string currentlyRecognised= string(1, static_cast<char>(byte));
	vector<string> stringBinaryEncoding;
	
	while (inFile.read(&byte, sizeof(char)))
	{
		if(dictionary.contains(currentlyRecognised+ string(1, static_cast<char>(byte))))
		{
			currentlyRecognised += string(1, static_cast<char>(byte));
		}
		else
		{
			if(index==maxIndex) 
			{
				digitCapacity++;
				maxIndex*=2;
			}
			stringBinaryEncoding.push_back(converter::decimalToBinary(dictionary.at(currentlyRecognised), digitCapacity));
			dictionary.insert(make_pair(currentlyRecognised+ string(1, static_cast<char>(byte)), index));
			index++;
			currentlyRecognised= string(1, static_cast<char>(byte));
		}		
	}
	if(index==maxIndex) 
	{
		digitCapacity++;
		maxIndex*=2;
	}
	stringBinaryEncoding.push_back(converter::decimalToBinary(dictionary.at(currentlyRecognised), digitCapacity));
	inFile.close();
	ofstream outFile2("out.txt", ios::binary);
	char tempChar = 0;
	int pos = 0;
	for (int i = 0; i < stringBinaryEncoding.size(); i++) {
		string tempBinaryEncoded = stringBinaryEncoding[i];
		for (int k = 0; k < tempBinaryEncoded.length(); k++) {
			if (tempBinaryEncoded[k] == '1') {
				tempChar = tempChar | 1;
			}
			pos++;
			if (pos == 8) {
				pos = 0;
				outFile2.write(&tempChar, sizeof(char));
				tempChar = 0;
			}
			tempChar = tempChar << 1;
		}
	}
	if (pos != 0) {
		tempChar <<= (7 - pos);
		outFile2.write(&tempChar, sizeof(char));
	}
	outFile2.close();
}
