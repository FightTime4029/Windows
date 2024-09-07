#pragma once

#include "HuffmanTree.hpp"
#include <iostream>

using std::string;
struct ByteInfo
{
	uch _ch;
	size_t _count;
	std::string _chCode;

	ByteInfo(size_t count = 0):_count(count)
	{}
	ByteInfo operator+(const ByteInfo& other)
	{
		return ByteInfo(_count + other._count);
	}

	bool operator>(const ByteInfo& other) const
	{
		return _count > other._count;
	}

	bool operator !=(const ByteInfo& other) const
	{
		return _count != other._count;
	}

	bool operator ==(const ByteInfo& other) const
	{
		return _count == other._count;
	}
};


class FileCompressHuffman
{
public:
	FileCompressHuffman();

	void CompressFile(const string& FilePath);
	void UNCompressFile(const string& FilePath);

private:
	void GetLine(FILE* fin, string& str);
	string GetFilePostFix(const string& filepath);
	void WriteHeadinfo(const string& filepath,FILE* fout);
	void GenerateHuffmanCode(HuffmanTreeNode<ByteInfo>* root);
	vector<ByteInfo> _fileinfo;

};
