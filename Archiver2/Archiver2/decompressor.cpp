#include "decompressor.h"
#include "converter.h"
#include "bytesWriter.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

void decompressor::decompress(string compressedFile)
{
	ifstream inFile(compressedFile, ios::binary);
	int sizeFileName;
	while (inFile.read((char*)&(sizeFileName), sizeof(int))) {
		unordered_map<int, string> dictionary;
		vector<string> output;
		for (int i = 0; i <= 255; i++)
		{
			dictionary.insert(make_pair(i, string(1, static_cast<char>(i))));
		}
		long long int fileSizeInBytes = 0;
		int digitCapacity = 9;
		int index = 256;
		int maxIndex = 512;
		string fileName;
		string tempStr;
		string prev;
		char byte;
		char* tempCharFileName = new char[sizeFileName];
		bool flag = true;
		inFile.read(tempCharFileName, sizeFileName);
		fileName = tempCharFileName;
		delete[] tempCharFileName;
		inFile.read((char*)&fileSizeInBytes, sizeof(fileSizeInBytes));
		for (int j = 0; j < fileSizeInBytes; j++) {
			inFile.read(&byte, sizeof(char));
			for (int i = 7; i >= 0; i--)
			{
				int bit = (byte >> i) & 1;
				tempStr += to_string(bit);
				if (tempStr.length() == digitCapacity) {
					if (flag) {
						int tempInt = converter::binaryToDecimal(tempStr);
						output.emplace_back(string(1, static_cast<char>(tempInt)));
						flag = false;
						prev = string(1, static_cast<char>(tempInt));
					}
					else {
						int tempInt = converter::binaryToDecimal(tempStr);
						if (dictionary.contains(tempInt)) {
							prev = prev + (dictionary.at(tempInt)[0]);
							dictionary.insert(make_pair(index++, prev));
							if (index == (maxIndex - 1)) {
								maxIndex = maxIndex * 2;
								digitCapacity++;
							}
							output.push_back(dictionary.at(tempInt));
						}
						else {
							dictionary.insert(make_pair(index++, (prev + prev[0])));
							if (index == (maxIndex - 1)) {
								maxIndex = maxIndex * 2;
								digitCapacity++;
							}
							output.push_back(prev + prev[0]);
						}
						prev = dictionary.at(tempInt);
					}
					tempStr.clear();
				}
			}
		}
		bytesWriter::writeUncomressedBytes(fileName, output);
	}
	inFile.close();
}
