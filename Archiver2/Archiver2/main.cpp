#include "compressor.h"
#include "decompressor.h"

int main()
{
	compressor compressorOfFiles;
	compressorOfFiles.compress();
	decompressor decompressorOfFiles;
	decompressorOfFiles.decompress();
}