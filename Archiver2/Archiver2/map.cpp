#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

int main()
{
	string pathToFile = "in.txt";
	cin>>pathToFile;
	
	/*char a[] = "''~~''~~''~~''~~";
	ofstream outFile(pathToFile, ios::binary);
	outFile.write(a, sizeof(char) *16);
	outFile.close();*/
	
	unordered_map<string, int> dictionary;
	for(int i=0;i<=255;i++)
	{
		dictionary.insert(make_pair(to_string(char(i)), i));
	}

	
	ifstream inFile(pathToFile, ios::binary);
	char byte;
	inFile.read(&byte, sizeof(char));
	string currentlyRecognised=to_string(char(byte));
	vector<int> binaryEncoding;
	int index=256;
	
	while (inFile.read(&byte, sizeof(char)))
	{
		if(dictionary.contains(currentlyRecognised+to_string(char(byte))))
		{
			currentlyRecognised+=to_string(char(byte));
		}
		else
		{
			binaryEncoding.push_back(dictionary.at(currentlyRecognised));
			dictionary.insert(make_pair(currentlyRecognised+to_string(char(byte)), index));
			index++;
			currentlyRecognised=to_string(char(byte));
		}		
	}
	binaryEncoding.push_back(dictionary.at(currentlyRecognised));
	for(int i=0;i<binaryEncoding.size();i++)
	{
		cout<<binaryEncoding[i]<<" ";
	}
	cout<<endl;
	inFile.close();
	
}

