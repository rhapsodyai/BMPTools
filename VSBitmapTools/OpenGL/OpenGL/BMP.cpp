#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
#include "freeglut.h"
#include <stdio.h>
#include "BMP.h"

#define WIDTH 320
#define HEIGHT 240


BMP::BMP(char *FileName) {
	Load(FileName);
	TexSet();
}

bool BMP::Load(char *FileName) {
	FILE *File;
	unsigned long size;                //Image Byte Size
	unsigned long i;                   //Counter
	unsigned short int planes;         //Device Planes
	unsigned short int bpp;            //NumPixels
	char temp;                         //Used for colors

	//File Open
	if ((File = fopen(FileName, "rb")) == NULL) {
		printf("No file found");
		return false;
	}

	//Move to the scrolling data for bitmap
	fseek(File, 18, SEEK_CUR);

	//Read in Bitmap Width
	if ((i = fread(&sizeX, 4, 1, File)) != 1) {
		printf("Read Error");
		return false;
	}

	//Read Height
	if ((i = fread(&sizeY, 4, 1, File)) != 1) {
		printf("Read Error");
		return false;
	}

	//Calculate the size of the image
	size = sizeX * sizeY * 3;                  //Read in the number of planes
	if ((fread(&planes, 2, 1, File)) != 1) {   //bmp is # 1
		printf("Can't read in the number of planes");
		return false;
	}

	if (planes != 1) {
		printf("Error: There is more than one plane");
		return false;
	}

	//Read in Pixel values
	if ((i = fread(&bpp, 2, 1, File)) != 1) {
		printf("Can't read the number of bits");
		return false;
	}

	//Error if not 24bpp
	if (bpp != 24) {
		printf("Is not a 24-bit image");
		return false;
	}

	//Pass by 24-bit to the color data (RGB) portion
	fseek(File, 24, SEEK_CUR);    //Read in data
	Data = (char *)malloc(size);
	if (Data == NULL) {
		printf("Error: Cannot allocate memory");
		return false;
	}

	if ((i = fread(Data, size, 1, File)) != 1) {
		printf("Error: No data");
		return false;
	}

	//bgr -> rgb
	for (i = 0; i<size; i += 3) {
		temp = Data[i];
		Data[i] = Data[i + 2];
		Data[i + 2] = temp;
	}

	return true;
}

void BMP::TexSet() {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	glBindTexture(GL_TEXTURE_2D, 0);
}