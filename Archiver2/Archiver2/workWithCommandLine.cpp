#include "workWithCommandLine.h"
#include "compressor.h"
#include "decompressor.h"
#include <filesystem>
#include <fstream>
#include "view.h"
using namespace std;

void workWithCommandLine::inputArgumentsOperate(int argc, char* argv[])
{
	if (argc >= 3)
	{
		if((strcmp(argv[1], "--compress") == 0) && (argc ==3))
		{
			string pathToFolder(argv[2]);
			filesystem::path p(pathToFolder);
			string archiveName=p.filename().string()+".lzw";
			ofstream out(archiveName, ios::binary);
			int mode=0;
			out.write((char*)&mode, sizeof(mode));
			out.close();
			for (const auto& entry : filesystem::directory_iterator(pathToFolder))
			{
				string fileName=entry.path().string();
				compressor compressorOfFiles;
				compressorOfFiles.compress(fileName, archiveName);
			}
		}
		else if ((strcmp(argv[1], "--compress") == 0) && (argc >= 4))
		{
			if (filesystem::exists(argv[2]))
				remove(argv[2]);
			ofstream out(argv[2], ios::binary);
			int mode=1;
			out.write((char*)&mode, sizeof(mode));
			out.close();
			for (int i = 3; i < argc; i++)
			{
				compressor compressorOfFiles;
				compressorOfFiles.compress(argv[i], argv[2]);
			}
		}
		else if (strcmp(argv[1], "--decompress") == 0)
		{
			decompressor decompressorOfFiles;
			decompressorOfFiles.decompress(argv[2]);
		}
		else
		{
			view::wrongArguments();
		}
	}
	else
	{
		view::notEnoughArguments();
	}
}
