#include "bytesWriter.h"
#include <fstream>
#include <vector>

using namespace std;

void bytesWriter::writeUncomressedBytes(std::string resultFile, vector<string> bytesInStr)
{
	ofstream outFile("result.pdf", ios::binary);
	for (int i = 0; i < bytesInStr.size(); i++) {
		for (int j = 0; j < bytesInStr[i].length(); j++) {
			outFile.write(&bytesInStr[i][j], sizeof(char));
		}
	}
	outFile.close();
}

void bytesWriter::writeCompressedBytes(vector<string> stringBinaryEncoding, string fileName)
{
	fileName=fileName.substr(0, fileName.find('.'));
	ofstream outFile2(fileName+".lzw", ios::binary);
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
