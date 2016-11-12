#ifndef __FLVSTRUCTPARSE_H__
#define __FLVSTRUCTPARSE_H__

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct FLVPosition
{
	int start;
	int len;
	FLVPosition()
	{
		start = 0;
		len = 0;
	}
}FLVPosition;

template <typename T>
class FLVObject
{
public:
	T value;
	FLVPosition pos;
};

class BaseStruct
{
public:
	FLVPosition pos;
};

class FLVHeader : public BaseStruct
{
public:	
	FLVObject<char[4]> signature;
	FLVObject<char> version;
	FLVObject<char> hasVideo;
	FLVObject<char> hasAudio;
	FLVObject<unsigned int> headerLen;

	FLVHeader()
	{
		memset(signature.value, 0, 4);
		version.value = 0;
		hasAudio.value = false;
		hasVideo.value = false;
		headerLen.value = 9;
	}
};

class FLVTag : public BaseStruct
{
public:	
	FLVObject<bool> encrypted;
	FLVObject<int> type;
	FLVObject<unsigned int> dataSize;
	FLVObject<unsigned int> timestamp;
	FLVObject<unsigned int> tagSize;
	struct FLVTag* next;

	FLVTag()
	{
		encrypted.value = false;
		type.value = 0;
		dataSize.value = 0;
		timestamp.value = 0;
		tagSize.value = 0;
		next = NULL;
	}
};

class FLVStruct : public BaseStruct
{
public:
	FLVHeader header;
	FLVTag* tagList;
	unsigned int dataLen;
	unsigned char* data;
	FLVStruct()
	{
		dataLen = 0;
		tagList = NULL;
		data = NULL;
	}
};

class FLVStructParse
{
public:
	FLVStructParse();
	~FLVStructParse();

public:
	FLVStruct* parseFile(char* fileName);

private:
	int LoadFile(char* fileName);
	int parseFlvHeader();
	int parseFlvTags();

private:
	FLVStruct* flv;
	int curIndex;
};

#endif