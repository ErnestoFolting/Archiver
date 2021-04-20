#include "decompressor.h"
#include "converter.h"
#include "bytesWriter.h"
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

void decompressor::decompress(string compressedFIle)
{
	vector<string> output;
	char byte;
	ifstream inFile(compressedFIle, ios::binary);
	int sizeFileName;
	cout << "Check" << endl;
	while (inFile.read((char*)&(sizeFileName), sizeof(int))) {
		unordered_map<int, string> dictionary;
		for (int i = 0; i <= 255; i++)
		{
			dictionary.insert(make_pair(i, string(1, static_cast<char>(i))));
		}
		int digitCapacity = 9;
		int index = 256;
		int maxIndex = 512;
		string pathToFile;
		long long int size = 0;
		string tempStr;
		bool flag = true;
		string prev;
		char* tempChar = new char[sizeFileName];
		inFile.read(tempChar, sizeFileName);
		pathToFile = tempChar;
		cout << tempChar << endl;
		inFile.read((char*)&size, sizeof(size));
		for (int j = 0; j < size; j++) {
			inFile.read(&byte, sizeof(char));
			for (int i = 7; i >= 0; i--)
			{
				int bit = (byte >> i) & 1;
				tempStr += to_string(bit);
				if (tempStr.length() == digitCapacity) {
					if (flag) {
						int tempInt = converter::binaryToDecimal(tempStr);
						output.push_back(string(1, static_cast<char>(tempInt)));
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
		bytesWriter::writeUncomressedBytes(pathToFile, output);
		output.clear();
		delete[] tempChar;
	}
	inFile.close();
}
