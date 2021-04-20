#include "compressor.h"
#include "decompressor.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc>=3)
	{
		if(strcmp(argv[1], "--compress")==0)
		{
			compressor compressorOfFiles;
			compressorOfFiles.compress(argv[3], argv[2]);
		}
		else if(strcmp(argv[1],"--decompress")==0)
		{
			decompressor decompressorOfFiles;
			decompressorOfFiles.decompress(argv[2]);
		}
	}
	else
	{
		cout<<"Not enough arguments!\n";
	}
}