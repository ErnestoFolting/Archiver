#include "view.h"

void view::decompressFinished(string file)
{
	cout << "Decompressing of " << file << " finished!" << endl;
}

void view::compressFinished(string file)
{
	cout << "Compressing to " << file<< " finished! " << endl;
}

void view::canNotOpenToCompress()
{
	cout << "Can not open a file to compress" << endl;
}

void view::compressStarted(string file)
{
	cout << file << " compressing started. Please, wait..." << endl;
}

void view::canNotOpenToDecompress()
{
	cout << "Can not open a file to decompress" << endl;
}

void view::decompressStarted(string file)
{
	cout << "Decompressing of " << file << " started. Please, wait..." << endl;
}

void view::wrongArguments()
{
	cout << "Wrong arguments!\n";
}

void view::notEnoughArguments()
{
	cout << "Not enough arguments \n";
}
