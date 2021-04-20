#include "compressor.h"
#include "decompressor.h"
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace std;

int main(int argc, char *argv[])
{
	if(argc>=3)
	{
		if(strcmp(argv[1], "--compress")==0)
		{
			if(filesystem::exists(argv[2]))
				remove(argv[2]);
			/*ofstream archive(argv[2], ios::binary);
			archive.close();*/
			for(int i=3; i<argc;i++)
			{
				compressor compressorOfFiles;
				compressorOfFiles.compress(argv[i], argv[2]);
			}
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