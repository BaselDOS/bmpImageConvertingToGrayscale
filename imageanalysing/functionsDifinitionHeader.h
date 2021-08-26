#pragma once
#include "functionDeclirationHeader.h"
#include "mainStructures.h"


struct Image readImage(FILE* fp, int height, int width)
{
	struct Image pic;
	int i;
	int bytesToread, numberOfrgb;
	pic.rgb = (struct RGB**)malloc(height * sizeof(void*));
	pic.height = height;
	pic.width = width;
	bytesToread = ((24 * width + 31) / 32) * 4;
	numberOfrgb = bytesToread / sizeof(struct RGB) + 1;
	for (i = height - 1; i >= 0; i--)
	{
		pic.rgb[i] = (struct RGB*)malloc(numberOfrgb * sizeof(struct RGB));
		fread(pic.rgb[i], 1, bytesToread, fp);
	}
	return pic;
}
void freeImage(struct Image pic)
{
	int i;
	for (i = pic.height - 1; i >= 0; i--) free(pic.rgb[i]);
	free(pic.rgb);
}



unsigned char grayscale(struct RGB rgb)
{
	return((0.3 * rgb.red) + (0.6 * rgb.green) + (0.1 * rgb.blue)) / 3;
}

void convert_RGB_Image2BlackAndWhite(struct Image pic)
{
	int i, j;
	for (i = 0; i < pic.height; i++)
		for (j = 0; j < pic.width; j++)
		{
			pic.rgb[i][j].red = pic.rgb[i][j].green = pic.rgb[i][j].blue = grayscale(pic.rgb[i][j]);
		}
}

int creatBWImage(struct BITMAP_header header, struct DIB_header dibHeader, struct Image pic)
{
	FILE* fpw = fopen("pic1.bmp", "w");
	if (fpw == NULL)return 0;
	int i;
	convert_RGB_Image2BlackAndWhite(pic);
	fwrite(header.name, 2, 1, fpw);
	fwrite(&header.size, 3 * sizeof(int), 1, fpw);
	fwrite(&dibHeader, sizeof(struct DIB_header), 1, fpw);
	for (i = pic.height - 1; i >= 0; i--)
	{
		fwrite(pic.rgb[i], ((24 * pic.width + 31) / 32) * 4 - 1, 1, fpw);
	}
	fclose(fpw);
	return 1;
}
void imageToText(struct Image image)
{
	int i, j;
	unsigned char gs;
	//0-31,32-63,64-95,96-127...
	char textpixel[] = { '@','#','%','O','a','-','.',' ' };
	for (i = 0; i < image.height; i++)
	{
		for (j = 0; j < image.width; j++)
		{
			gs = grayscale(image.rgb[i][j]);
			printf("%c", textpixel[7 - gs / 32]);

		}
		printf("\n");
	}
}
int openbmpfile()
{
	FILE* fp = fopen("Tom.bmp", "rb");
	if (fp == NULL) return 0;
	struct BITMAP_header header;
	struct DIB_header dibHeader;
	fread(header.name, 2, 1, fp);
	fread(&header.size, 3 * sizeof(int), 1, fp);
	printf("first two caracetrs%c%c\n", header.name[0], header.name[1]);
	printf("size:%d\n", header.size);
	printf("offset:%d\n", header.image_offset);
	fread(&dibHeader, sizeof(struct DIB_header), 1, fp);
	printf("header size:%d\nWidth:%d\nHeight:%d\nColor planes:%d\nBits for pixel:%d\nCompression:%d\nImage size:%d\n", dibHeader.headerSize, dibHeader.width, dibHeader.height, dibHeader.colorplanes, dibHeader.bitsperpixel, dibHeader.compression, dibHeader.image_size);
	fseek(fp, header.image_offset, SEEK_SET);//move to the starting point of the image
	struct Image image = readImage(fp, dibHeader.height, dibHeader.width);
	imageToText(image);
	creatBWImage(header, dibHeader, image);
	fclose(fp);
	freeImage(image);
	return 1;

}
