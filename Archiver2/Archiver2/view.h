#pragma once
#include <string>
#include <iostream>
using namespace std;
class view
{
public:
	static void decompressFinished(string file);
	static void compressFinished(string file);
	static void canNotOpenToCompress();
	static void compressStarted(string file);
	static void canNotOpenToDecompress();
	static void decompressStarted(string file);
	static void wrongArguments();
	static void notEnoughArguments();
};

