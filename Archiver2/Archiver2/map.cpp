#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

int main()
{
	string pathToFile = "in.txt";
	//cin>>pathToFile;
	
	char a[] = "aaaafbc gcncn ";
	ofstream outFile(pathToFile, ios::binary);
	outFile.write(a, sizeof(char) * 14);
	outFile.close();
	
	unordered_map<string, int> dictionary;
	for(int i=0;i<=255;i++)
	{
		dictionary.insert(make_pair(to_string(char(i)), i));
	}

	
	ifstream inFile(pathToFile, ios::binary);
	char byte;
	vector<int> binaryEncoding;
	while (inFile.read(&byte, sizeof(char)))
	{
		cout<<byte<<" ";
		
	}
}

