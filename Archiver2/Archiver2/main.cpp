#include "compressor.h"
#include "decompressor.h"
#include <iostream>

using namespace std;

int main()
{
	std::cout<<"compress(0) decompress(1): ";
	int choice;
	cin>>choice;
	if(!choice)
	{
		std::string pathToFile;
		cin>>pathToFile;
		compressor compressorOfFiles(pathToFile);
		compressorOfFiles.compress();
	}
	else
	{
		std::string pathToCompressedFile;
		cin>>pathToCompressedFile;
		decompressor decompressorOfFiles;
		decompressorOfFiles.decompress(pathToCompressedFile);
	}
}