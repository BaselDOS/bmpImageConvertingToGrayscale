#pragma once
#include "mainStructures.h"

struct Image readImage(FILE* fp, int height, int width);
void freeImage(struct Image pic);
unsigned char grayscale(struct RGB rgb);
void convert_RGB_Image2BlackAndWhite(struct Image pic);
int creatBWImage(struct BITMAP_header header, struct DIB_header dibHeader, struct Image pic);
void imageToText(struct Image image);
int openbmpfile();
