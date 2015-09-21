#include <iostream>
#include "freeglut.h"
#include "BMP.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define SLEEP_FACTOR 2000

/*
Author: Melissa Auclaire
Website: http://blog.vr-cubed.com
Email: melissa@vr-cubed.com
Created on: 9/17/2015
*/

using namespace std;

//global variables
int WindowPositionX = 100;
int WindowPositionY = 100;
int WindowWidth = 640;
int WindowHeight = 480;
char WindowTitle[] = "Sprite Animation Example";


BMP *bmp;
BMP *bmp2;
BMP *bmp3;
BMP *bmp4;
BMP *bmp5;
BMP *bmp6;
BMP *bmp7;
BMP *bmp8;
BMP *bmp9;
BMP *bmp10;
BMP *bmp11;
BMP *bmp12;
BMP *bmp13;
BMP *bmp14;
BMP *bmp15;
BMP *bmp16;

//function prototypes
void sleep(int);
void drawImage(BMP* tmpBMP);

void Initialize();
void Display();
void Idle();
void Reshape(int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);


//Main entry point
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitWindowPosition(WindowPositionX, WindowPositionY);
	glutInitWindowSize(WindowWidth, WindowHeight);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(WindowTitle);
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutIdleFunc(Idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutPassiveMotionFunc(PassiveMotion);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);
	Initialize();
	glutMainLoop();
	return 0;
}


//Function to Initialize glut
void Initialize() {
	//Load texture
	bmp = new BMP("walkcycle1.bmp");
	bmp2 = new BMP("walkcycle2.bmp");
	bmp3 = new BMP("walkcycle3.bmp");
	bmp4 = new BMP("walkcycle4.bmp");
	bmp5 = new BMP("walkcycle5.bmp");
	bmp6 = new BMP("walkcycle6.bmp");
	bmp7 = new BMP("walkcycle7.bmp");
	bmp8 = new BMP("walkcycle8.bmp");
	bmp9 = new BMP("walkcycle9.bmp");
	bmp10 = new BMP("walkcycle10.bmp");
	bmp11 = new BMP("walkcycle11.bmp");
	bmp12 = new BMP("walkcycle12.bmp");
	bmp13 = new BMP("walkcycle13.bmp");
	bmp14 = new BMP("walkcycle14.bmp");
	bmp15 = new BMP("walkcycle15.bmp");
	bmp16 = new BMP("walkcycle16.bmp");

	glClearColor(0, 0, 0, 0); // moved this line to be in the init function
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1, 0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
}

//Called while idle
void Idle() {
	glutPostRedisplay();
}

//Called when window is resized
void Reshape(int x, int y) {
	WindowWidth = x;
	WindowHeight = y;
	if (WindowWidth < 1) WindowWidth = 1;
	if (WindowHeight < 1) WindowHeight = 1;
}

//Draw window

//Upside down
/*
glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 0);
glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 480);
glTexCoord2f(1.0f, 1.0f); glVertex2d(640,480);
glTexCoord2f(1.0f, 0.0f); glVertex2d(640, 0);
*/

//Rightside up, about face
/*
glTexCoord2f(0.0f, 0.0f); glVertex2d(640,480);
glTexCoord2f(0.0f, 1.0f); glVertex2d(640, 0);
glTexCoord2f(1.0f, 1.0f); glVertex2d(0, 0);
glTexCoord2f(1.0f, 0.0f); glVertex2d(0, 480);
*/

void Display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//animation sequence
	drawImage(bmp);
	drawImage(bmp2);
	drawImage(bmp3);
	drawImage(bmp4);
	drawImage(bmp5);
	drawImage(bmp6);
	drawImage(bmp7);
	drawImage(bmp8);
	drawImage(bmp9);
	drawImage(bmp10);
	drawImage(bmp11);
	drawImage(bmp12);
	drawImage(bmp13);
	drawImage(bmp14);
	drawImage(bmp15);
	drawImage(bmp16);

}

//Mouse input
void Mouse(int button, int state, int x, int y) {
}

//Mouse motion while draggind
void Motion(int x, int y) {
}

//Mouse passive motion while moving
void PassiveMotion(int x, int y) {
}

//Keyboard input
void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '\033':
		exit(0);
		break;

	default:
		break;
	}
}

//Input for Special keys
void Special(int key, int x, int y) {
}


void sleep(int cnt) {
	int ContinueSwitch = 0;
	double counter = 0.0;
	while (true) {
		counter++;
		if (ContinueSwitch == 1)
			break;

		else if (counter == cnt*10000.0)
			ContinueSwitch = 1;
	}
}

void drawImage(BMP* tmpBMP) {
	glEnable(GL_TEXTURE_2D);//Enable Texture
	glBindTexture(GL_TEXTURE_2D, tmpBMP->texture);
	glEnable(GL_ALPHA_TEST);//Begin Alpha Test
	glBegin(GL_POLYGON);

	//Rightside up, Facing Right way
	glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 480);
	glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2d(640, 0);
	glTexCoord2f(1.0f, 0.0f); glVertex2d(640, 480);
	glEnd();

	glDisable(GL_ALPHA_TEST);//End Alpha Test
	glDisable(GL_TEXTURE_2D);//Disabe Texture

	glutSwapBuffers();

	sleep(SLEEP_FACTOR);
}
