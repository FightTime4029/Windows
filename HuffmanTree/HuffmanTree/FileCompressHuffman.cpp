#define _CRT_SECURE_NO_WARNINGS

#include "FileCompressHuffman.h"
#include "HuffmanTree.hpp"
#include <string>
//1.解压文件中如果有中文，因为ASCII编码问题 可能会是负数 但是我们使用char去接收或者下标去使用
//会导致崩溃问题 所以需要把char都改成unsigned  char
//2.如果我们使用文本文件去写入读取，又会导致漏读或者少读 因为文本文件可能会写入FF（-1） 而判断文件结尾就是
//通过-1去判断 所以我们使用二进制读取写入


//生成哈夫曼编码
void FileCompressHuffman::GenerateHuffmanCode(HuffmanTreeNode<ByteInfo>* root)
{
	if (root == nullptr)
		return;

	GenerateHuffmanCode(root->_left);
	GenerateHuffmanCode(root->_right);

	//发现huffman编码chCode 编码不对对cur进行了逆置但是没有效果，应该对root进行逆置
	if (root->_left == nullptr && root->_right == nullptr)
	{
		//叶子节点
		string& chCode = _fileinfo[root->_weight._ch]._chCode;
		HuffmanTreeNode<ByteInfo>* cur = root;
		HuffmanTreeNode<ByteInfo>* parent = cur->_parent;
		while (parent)
		{
			if (parent->_left == cur)
			{
				chCode += '0';
			}
			else
			{
				chCode += '1';
			}


			cur = parent;
			parent = cur->_parent;
		}
		reverse(chCode.begin(), chCode.end());
	}
}

//获取文件后缀
string FileCompressHuffman::GetFilePostFix(const string& filepath)
{
	return filepath.substr(filepath.find_last_of('.') + 1);
}

void FileCompressHuffman::WriteHeadinfo(const string& filepath, FILE* fout)
{
	//获得文件后缀
	string headinfo;
	headinfo += GetFilePostFix(filepath);
	headinfo += '\n';
	//获得频次信息
	size_t appearLineCount = 0;
	string chinfo;
	for (auto& e : _fileinfo)
	{
		if (e._count == 0)
			continue;

		chinfo += e._ch;
		chinfo += ':';
		chinfo += std::to_string(e._count);
		chinfo += '\n';
		appearLineCount++;
	}
	headinfo += std::to_string(appearLineCount);
	headinfo += '\n';

	fputs(headinfo.c_str(), fout);
	fputs(chinfo.c_str(),  fout);
}


void FileCompressHuffman::GetLine(FILE* fin, string& str)
{
	while (!feof(fin))
	{
		char ch = fgetc(fin);
		if (ch == '\n')
			break;
		str += ch;
	}
}
FileCompressHuffman::FileCompressHuffman()
{
	_fileinfo.resize(256);

	for (int i = 0; i < 256; i++)
	{
		_fileinfo[i]._ch = i;
	}
}

void FileCompressHuffman::CompressFile(const string& FilePath)
{
	typedef HuffmanTreeNode<ByteInfo> Node;
	//1.统计源文件中 字符出现的次数
	FILE* fIn = fopen(FilePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		std::cout << "待压缩文件无法找到！" << std::endl;
		return;
	}
	uch fdbuffer[1024];
	while (true)
	{
		int size = fread(fdbuffer, 1, 1024, fIn);
		if (size == 0)
			break;

		for (int i = 0; i < size; i++)
		{
			_fileinfo[fdbuffer[i]]._count++;
		}
	}
	//2.用统计结果创建huffman树
	ByteInfo valid;
	HuffmanTree<ByteInfo> hf(_fileinfo, valid);

	//3.获取哈夫曼编码
	// 
	// 压缩和解压缩写完之后发现问题！ 这个问题在解压缩之后字符串顺序和出现次数都不正确
	//一.我先检查huffman编码
	GenerateHuffmanCode(hf.GetRoot());

	//4.将文件后缀 数字串及出现次数 的信息放入压缩文件头部
	
	//二.检查写入信息是否正确，屏蔽解压代码查看写入后缀信息等无问题
	FILE* fout = fopen("1zip.txt", "wb");
	WriteHeadinfo(FilePath, fout);


	
	//5.用获取到的编码对源文件进行改写

	//问题1： 我们上一次读过文件之后，文件指针在文件末尾 需要重置文件指针
	fseek(fIn, 0, SEEK_SET);
	uch _bit = 0;
	int _num = 0;

	while (true)
	{
		size_t size = fread(fdbuffer, 1, 1024, fIn);
		if (size == 0)
			break;

		for (int i = 0; i < size; i++)
		{
			string& chCode = _fileinfo[fdbuffer[i]]._chCode;
			for (int j = 0; j < chCode.size(); j++)
			{
				_bit <<= 1;

				if (chCode[j] == '1')
					_bit |= 1;
				_num++;
				
				if (8 == _num)
				{
					fputc(_bit, fout);
					_bit = 0;
					_num = 0;
				}
			}
		}
	}
	//三.写入文件信息没问题，再检测改写信息是否有问题，发现最后不满8位的我们需要将低位数据移到高位
	//没有使用右移等 导致写入数据出现问题(可能是导致问题的关键)
	if (_num > 0 && _num < 8)
	{
		_bit <<=(8 - _num);
		fputc(_bit, fout);
	}

	fclose(fIn);
	fclose(fout);
}




//解压缩
void FileCompressHuffman::UNCompressFile(const string& FilePath)
{
	//1. a解压缩需要的信息
	
	string unCompressFile("zip.");
	string FileName;
	FILE* fIn = fopen(FilePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		std::cout << "解压缩文件路径不对" << std::endl;
	}
	GetLine(fIn, FileName);
	unCompressFile += FileName;
	
	// b.读取频次信息
	FileName = "";
	GetLine(fIn, FileName);
	size_t Linecount = atoi(FileName.c_str());
	for (size_t i = 0; i < Linecount; i++)
	{
		FileName = "";
		//注意：换行需要单独处理
		GetLine(fIn, FileName);
		if (FileName == "")
		{
			FileName += '\n';
			GetLine(fIn,FileName);
		}

		_fileinfo[(uch)FileName[0]]._ch = (uch)FileName[0];
		_fileinfo[(uch)FileName[0]]._count = (uch)atoi(FileName.c_str() + 2);
	}

	//2.还原哈夫曼树

	HuffmanTree<ByteInfo> hf(_fileinfo, ByteInfo());

	//3.解压缩
	FILE* fout = fopen(unCompressFile.c_str(), "wb");
	uch rdbuffer[1024];
	HuffmanTreeNode<ByteInfo>* cur = hf.GetRoot();
	int FileNum = cur->_weight._count;
	while(true)
	{
		int size = fread(rdbuffer, 1, 1024, fIn);
		if (size == 0)
			break;
		for (int i = 0; i < size; i++)
		{
			uch ch = rdbuffer[i];
			for (int j = 0; j < 8; j++)
			{
				if (ch & 0x80)
					cur = cur->_right;
				else
					cur = cur->_left;

				ch <<= 1;

				if (cur->_left == nullptr && cur->_right == nullptr)
				{
					fputc(cur->_weight._ch, fout);
					cur = hf.GetRoot();
					FileNum--;
					if (FileNum ==0)
						break;
				}
			}
		}
	}
	fclose(fIn);
	fclose(fout);

}

