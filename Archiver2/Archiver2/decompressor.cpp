#include "decompressor.h"
#include "converter.h"
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

void decompressor::decompress()
{
	int digitCapacity = 9;
	int maxIndex = 512;
	int index = 256;
	vector<string> output;
	unordered_map<int, string> dictionary;
	for (int i = 0; i <= 255; i++)
	{
		dictionary.insert(make_pair(i, string(1, static_cast<char>(i))));
	}
	char byte;
	ifstream inFile("out.txt", ios::binary);
	ofstream outFile("result.pdf", ios::binary);
	string tempStr;
	bool flag = true;
	string prev;
	while (inFile.read(&byte, sizeof(char))) {
		for (int i = 7; i >= 0; i--)
		{
			int bit = (byte >> i) & 1;
			tempStr += to_string(bit);
			if (tempStr.length() == digitCapacity) {
				if (flag) {
					int tempInt = converter::binToDec(tempStr);
					output.push_back(string(1,static_cast<char>(tempInt)));
					flag = false;
					prev = string(1, static_cast<char>(tempInt));
				}
				else {
					int tempInt = converter::binToDec(tempStr);
					if (dictionary.contains(tempInt)) {
						prev = prev + (dictionary.at(tempInt)[0]);
						dictionary.insert(make_pair(index++, prev));
						if (index == (maxIndex-1)) {
							maxIndex = maxIndex * 2;
							digitCapacity++;
						}
						output.push_back(dictionary.at(tempInt));
					}
					else {
						dictionary.insert(make_pair(index++, (prev + prev[0])));
						if (index == (maxIndex-1)) {
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
	inFile.close();
	for (int i = 0; i < output.size(); i++) {
		for (int j = 0; j < output[i].length(); j++) {
			outFile.write(&output[i][j], sizeof(char));
		}
	}
	outFile.close();
}
