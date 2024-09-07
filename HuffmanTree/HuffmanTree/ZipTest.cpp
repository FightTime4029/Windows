#define _CRT_SECURE_NO_WARNINGS

#include "FileCompressHuffman.h"


int main()
{
	FileCompressHuffman fch;
	fch.CompressFile("1.txt");
	fch.UNCompressFile("1zip.txt");
	return 0;
}