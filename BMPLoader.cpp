/************************************************************************
�@�@BMPLoader.cpp

�@�@BMP Texture Loader

�@�@Date : October 11, 2007
�@�@Version : 1.0
�@�@Author : Pocol
�@�@Memo :
*************************************************************************/

//
//�@include
//
#include <fstream>
#include <windows.h>
#include "BMPLoader.h"
using namespace std;

//�@disable Warning C4996
#pragma warning(disable : 4996)


//////////////////////////////////////////////////////////////////////////
//�@�@BMPImage class
//////////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------------------------------------------------
//�@�@BMPImage
//�@�@Desc : �R���X�g���N�^
//-----------------------------------------------------------------------------------------------------
BMPImage::BMPImage()
{
	imageSize = 0;
	imageData = NULL;
	format = GL_RGB;
	internalFormat = GL_RGB;
	width = 0;
	height = 0;
	bpp = 0;
	ID = 0;
}

//-----------------------------------------------------------------------------------------------------
//�@�@~BMPImage
//�@�@Desc : �f�X�g���N�^
//-----------------------------------------------------------------------------------------------------
BMPImage::~BMPImage()
{
	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}
}

//-----------------------------------------------------------------------------------------------------
//�@�@ReadBMP
//�@�@Desc : BMP�t�@�C���̓ǂݍ���
//-----------------------------------------------------------------------------------------------------
bool BMPImage::ReadBMP(const char *filename)
{
	FILE *fp;

	BITMAPINFOHEADER bitmapInfoHeader;
	BITMAPFILEHEADER header;
	GLubyte temp = 0;

	//�@�t�@�C�����J��
	if ( (fp = fopen(filename, "rb")) == NULL )
	{
		cout << "Error : �w�肳�ꂽ�t�@�C�����J���܂���\n";
		cout << "File Name : " << filename << endl;
		return false;
	}

	//�@�w�b�_�[���̓ǂݎ��
	fread(&header, sizeof(BITMAPFILEHEADER), 1, fp);

	//�@�t�@�C���`�F�b�N
	if ( header.bfType != 0x4d42 )
	{
		cout << "Error : Bitmap�t�@�C���ł͂���܂���\n";
		fclose(fp);
		return false;
	}

	//�@�w�b�_�[���̓ǂݎ��
	fread(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	//�@���ƍ������擾
	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;

	if ( bitmapInfoHeader.biSizeImage == 0 )
	{
		bitmapInfoHeader.biSizeImage = bitmapInfoHeader.biWidth * bitmapInfoHeader.biHeight * 3;
	}

	fseek(fp, header.bfOffBits, SEEK_SET);

	//�@�f�[�^�T�C�Y�����肵�C���������m��
	imageSize = bitmapInfoHeader.biSizeImage;
	imageData = new GLubyte [imageSize];

	//�@�G���[�`�F�b�N
	if ( !imageData )
	{
		cout << "Error : ���������m�ۂł��܂���ł���\n";
		delete [] imageData;
		fclose(fp);
		return false;
	}

	//�@�s�N�Z���f�[�^�̓ǂݍ���
	fread(imageData, 1, bitmapInfoHeader.biSizeImage, fp);

	//�@BGR�@���@RGB�ɕϊ�
	for ( int i=0; i<(int)imageSize; i+=3 )
	{
		temp = imageData[i+0];
		imageData[i+0] = imageData[i+2];
		imageData[i+2] = temp;
	}

	//�@�t�@�C�������
	fclose(fp);

	return true;
}

//-----------------------------------------------------------------------------------------------------
//�@�@Load
//�@�@Desc : BMP�t�@�C����ǂݍ��݁C�e�N�X�`���𐶐�
//-----------------------------------------------------------------------------------------------------
GLuint BMPImage::Load(const char *filename)
{
	if ( !ReadBMP(filename) )
		return 0;

	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, width, height, format, GL_UNSIGNED_BYTE, imageData );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	if ( imageData )
	{
		delete [] imageData;
		imageData = NULL;
	}
	return ID;
}
