#include "bytesWriter.h"
#include "byteCounter.h"
#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void bytesWriter::writeUncomressedBytes(std::string resultFile, vector<string> bytesInStr)
{
	ofstream outFile(resultFile, ios::binary);
	for (int i = 0; i < bytesInStr.size(); i++) {
		for (int j = 0; j < bytesInStr[i].length(); j++) {
			outFile.write(&bytesInStr[i][j], sizeof(char));
		}
	}
	outFile.close();
}

void bytesWriter::writeCompressedBytes(vector<string> stringBinaryEncoding, string archiveName, string fileName)
{
	long long int size = byteCounter::getSizeOfFile(stringBinaryEncoding);
	ofstream outFile2(archiveName, ios::binary|ios::app|ios::out);
	int sizeFileName = fileName.length() + 1;
	outFile2.write((char*)&(sizeFileName), sizeof(int));
	outFile2.write((char*)fileName.data(), sizeFileName);
	outFile2.write((char*)&size, sizeof(size));
	char tempChar = 0;
	int pos = 0;
	long long int sizeOfFile;
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
