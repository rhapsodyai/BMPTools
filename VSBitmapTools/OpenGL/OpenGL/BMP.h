//BMP.h
#ifndef __BMP_H_INCLUDED //if x.h hasn't been included yet...
#define __BMP_H_INCLUDED //#define this so the compiler knows it has been included

class BMP {
public:
	unsigned long sizeX;  //‰¡
	unsigned long sizeY; //c
	char *Data;  //‰æ‘œƒf[ƒ^Ši”[
	bool Load(char *filename);
	GLuint texture;
	void TexSet();
	BMP(char *FileName);
};

#endif

