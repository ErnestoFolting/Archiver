#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>
#include <cmath>
#include <bitset>

using namespace std;

string bin(int number, int digitCapacity) {
    string binary;
	if(number==0) binary="0";
    while(number > 0){
        binary=to_string(number % 2) + binary;
        number/=2;
    }
    int len = binary.length();
    while (len < digitCapacity) {
        binary = "0" + binary;
    	len++;
    }
    return binary;
}
int binToDec(string bin);
void decoder();

int main()
{
	string pathToFile = "in.txt";
	//cin>>pathToFile;
	
	char a[] = "''~~''~~''~~''~~";
	ofstream outFile(pathToFile, ios::binary);
	outFile.write(a, sizeof(char) *16);
	outFile.close();
	
	unordered_map<string, int> dictionary;
	for(int i=0;i<=255;i++)
	{
		dictionary.insert(make_pair(to_string(char(i)), i));
	}
	cout << binToDec("0100101");
	
	ifstream inFile(pathToFile, ios::binary);
	char byte;
	inFile.read(&byte, sizeof(char));
	string currentlyRecognised=to_string(char(byte));
	vector<int> binaryEncoding;
	vector<string> stringBinaryEncoding;
	int digitCapacity=9;
	int maxIndex=512;
	int index=256;
	
	while (inFile.read(&byte, sizeof(char)))
	{
		if(dictionary.contains(currentlyRecognised+to_string(char(byte))))
		{
			currentlyRecognised+=to_string(char(byte));
		}
		else
		{
			if(index==maxIndex) 
			{
				digitCapacity++;
				maxIndex*=2;
			}
			binaryEncoding.push_back(dictionary.at(currentlyRecognised));
			stringBinaryEncoding.push_back(bin(dictionary.at(currentlyRecognised), digitCapacity));
			dictionary.insert(make_pair(currentlyRecognised+to_string(char(byte)), index));
			index++;
			currentlyRecognised=to_string(char(byte));
		}		
	}
	if(index==maxIndex) 
	{
		digitCapacity++;
		maxIndex*=2;
	}
	binaryEncoding.push_back(dictionary.at(currentlyRecognised));
	stringBinaryEncoding.push_back(bin(dictionary.at(currentlyRecognised), digitCapacity));
	for(int i=0;i<binaryEncoding.size();i++)
	{
		cout<<binaryEncoding[i]<<" ";
	}
	cout<<endl;
	for(int i=0;i<binaryEncoding.size();i++)
	{
		cout<<stringBinaryEncoding[i]<<" ";
	}
	cout<<endl;
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
	decoder();
}

void decoder() {
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
	ofstream outFile("result.txt", ios::binary);
	string tempStr;
	bool flag = true;
	while (inFile.read(&byte, sizeof(char))) {
		for (int i = 7; i >= 0; i--)
		{
			int bit = (byte >> i) & 1;
			tempStr += to_string(bit);
			//cout << endl << tempStr << endl;
			if (tempStr.length() == digitCapacity) {
				if (flag) {
					int tempInt = binToDec(tempStr);
					//cout << "tempInt" << tempInt << endl;
					//cout << endl << "check" << static_cast<char>(tempInt) << endl;
					output.push_back(string(1,static_cast<char>(tempInt)));
					flag = false;
					cout << output.back();
				}
				else {
					string prev = output.back();
					int tempInt = binToDec(tempStr);
					prev += ( dictionary.at(tempInt)[0]);
					cout << endl << "prev " << prev << endl;
					dictionary.insert(make_pair(index++, prev));
					if (index == maxIndex) {
						maxIndex *= 2;
						digitCapacity++;
					}
					cout << endl << "dictionary.at(tempInt)" << dictionary.at(tempInt) << endl;
					output.push_back(dictionary.at(tempInt));
				}
				tempStr.clear();
			}
		}
		//cout << " ";
	}
	inFile.close();
	outFile.close();
	//cout << output.size() << endl;
	for (int i = 0; i < output.size(); i++) {
		for (int j = 0; j < output[i].size(); j++) {
			cout << "Output:" << " " << (output[i][j]) << endl;
		}
	}
}
int binToDec(string bin) {
	int dec = 0;
	for (int i = 0; i < bin.length(); i++) {
		if (bin[i] == '1') {
			dec += pow(2, bin.length() - i-1);
		}
	}
	return dec;
}