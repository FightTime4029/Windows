#define _CRT_SECURE_NO_WARNINGS

#include "FileCompressHuffman.h"
#include "HuffmanTree.hpp"
#include <string>
//1.��ѹ�ļ�����������ģ���ΪASCII�������� ���ܻ��Ǹ��� ��������ʹ��charȥ���ջ����±�ȥʹ��
//�ᵼ�±������� ������Ҫ��char���ĳ�unsigned  char
//2.�������ʹ���ı��ļ�ȥд���ȡ���ֻᵼ��©�������ٶ� ��Ϊ�ı��ļ����ܻ�д��FF��-1�� ���ж��ļ���β����
//ͨ��-1ȥ�ж� ��������ʹ�ö����ƶ�ȡд��


//���ɹ���������
void FileCompressHuffman::GenerateHuffmanCode(HuffmanTreeNode<ByteInfo>* root)
{
	if (root == nullptr)
		return;

	GenerateHuffmanCode(root->_left);
	GenerateHuffmanCode(root->_right);

	//����huffman����chCode ���벻�Զ�cur���������õ���û��Ч����Ӧ�ö�root��������
	if (root->_left == nullptr && root->_right == nullptr)
	{
		//Ҷ�ӽڵ�
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

//��ȡ�ļ���׺
string FileCompressHuffman::GetFilePostFix(const string& filepath)
{
	return filepath.substr(filepath.find_last_of('.') + 1);
}

void FileCompressHuffman::WriteHeadinfo(const string& filepath, FILE* fout)
{
	//����ļ���׺
	string headinfo;
	headinfo += GetFilePostFix(filepath);
	headinfo += '\n';
	//���Ƶ����Ϣ
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
	//1.ͳ��Դ�ļ��� �ַ����ֵĴ���
	FILE* fIn = fopen(FilePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		std::cout << "��ѹ���ļ��޷��ҵ���" << std::endl;
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
	//2.��ͳ�ƽ������huffman��
	ByteInfo valid;
	HuffmanTree<ByteInfo> hf(_fileinfo, valid);

	//3.��ȡ����������
	// 
	// ѹ���ͽ�ѹ��д��֮�������⣡ ��������ڽ�ѹ��֮���ַ���˳��ͳ��ִ���������ȷ
	//һ.���ȼ��huffman����
	GenerateHuffmanCode(hf.GetRoot());

	//4.���ļ���׺ ���ִ������ִ��� ����Ϣ����ѹ���ļ�ͷ��
	
	//��.���д����Ϣ�Ƿ���ȷ�����ν�ѹ����鿴д���׺��Ϣ��������
	FILE* fout = fopen("1zip.txt", "wb");
	WriteHeadinfo(FilePath, fout);


	
	//5.�û�ȡ���ı����Դ�ļ����и�д

	//����1�� ������һ�ζ����ļ�֮���ļ�ָ�����ļ�ĩβ ��Ҫ�����ļ�ָ��
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
	//��.д���ļ���Ϣû���⣬�ټ���д��Ϣ�Ƿ������⣬���������8λ��������Ҫ����λ�����Ƶ���λ
	//û��ʹ�����Ƶ� ����д�����ݳ�������(�����ǵ�������Ĺؼ�)
	if (_num > 0 && _num < 8)
	{
		_bit <<=(8 - _num);
		fputc(_bit, fout);
	}

	fclose(fIn);
	fclose(fout);
}




//��ѹ��
void FileCompressHuffman::UNCompressFile(const string& FilePath)
{
	//1. a��ѹ����Ҫ����Ϣ
	
	string unCompressFile("zip.");
	string FileName;
	FILE* fIn = fopen(FilePath.c_str(), "rb");
	if (fIn == nullptr)
	{
		std::cout << "��ѹ���ļ�·������" << std::endl;
	}
	GetLine(fIn, FileName);
	unCompressFile += FileName;
	
	// b.��ȡƵ����Ϣ
	FileName = "";
	GetLine(fIn, FileName);
	size_t Linecount = atoi(FileName.c_str());
	for (size_t i = 0; i < Linecount; i++)
	{
		FileName = "";
		//ע�⣺������Ҫ��������
		GetLine(fIn, FileName);
		if (FileName == "")
		{
			FileName += '\n';
			GetLine(fIn,FileName);
		}

		_fileinfo[(uch)FileName[0]]._ch = (uch)FileName[0];
		_fileinfo[(uch)FileName[0]]._count = (uch)atoi(FileName.c_str() + 2);
	}

	//2.��ԭ��������

	HuffmanTree<ByteInfo> hf(_fileinfo, ByteInfo());

	//3.��ѹ��
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

