#pragma once
#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS


struct BITMAP_header
{
	char name[2];
	unsigned int size; //using it because sizeof(int) is 4 bits in our machine
	int reserved;
	unsigned int image_offset; // offset from where image starts in file
};

struct DIB_header
{
	unsigned int headerSize;
	unsigned  int width;
	unsigned  int height;
	unsigned short int colorplanes;
	unsigned short int bitsperpixel;
	unsigned int compression;
	unsigned int image_size;
	unsigned int temp[4];
};

struct RGB
{
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

struct Image
{
	int height;
	int width;
	struct RGB** rgb;
};
