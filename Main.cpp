#include <iostream>
#include <GL/glut.h>
#include "BMP.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

using namespace std;

//　global
int WindowPositionX = 100;
int WindowPositionY = 100;
int WindowWidth = 640;
int WindowHeight = 480;
char WindowTitle[] = "Texture Mapping (3) - BMP File -";
BMP *bmp;

//　prototype
void Initialize();
void Display();
void Idle();
void Reshape(int x, int y);
void Mouse(int button, int state, int x, int y);
void Motion(int x, int y);
void PassiveMotion(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void Special(int key, int x, int y);


//----------------------------------------------------------------------------------------------------
//　　main
//　　Desc : メインエントリーポイント
//----------------------------------------------------------------------------------------------------
int main( int argc, char **argv )
{
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


//----------------------------------------------------------------------------------------------------
//　　Initialize
//　　Desc : 初期化処理
//----------------------------------------------------------------------------------------------------
void Initialize()
{

	//　テクスチャのロード
	bmp = new BMP("walkcycle1.bmp");

	glClearColor(0,0,0,0); // moved this line to be in the init function
        glDisable(GL_DEPTH_TEST);
    
        // next four lines are new
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WINDOW_WIDTH-1, WINDOW_HEIGHT-1, 0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

}

//---------------------------------------------------------------------------------------------------
//　　Idle
//　　Desc : アイドリング時の処理
//---------------------------------------------------------------------------------------------------
void Idle()
{
	glutPostRedisplay();
}

//---------------------------------------------------------------------------------------------------
//　　Reshape
//　　Desc : サイズ変更
//---------------------------------------------------------------------------------------------------
void Reshape(int x, int y)
{
	WindowWidth = x;
	WindowHeight = y;
	if ( WindowWidth < 1 ) WindowWidth = 1;
	if ( WindowHeight < 1 ) WindowHeight = 1;
}

//---------------------------------------------------------------------------------------------------
//　　Display
//　　Desc : ウィンドウへの描画
//---------------------------------------------------------------------------------------------------
void Display() {

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


    glEnable(GL_TEXTURE_2D);//Enable Texture
    glBindTexture( GL_TEXTURE_2D, bmp->texture);
    glEnable(GL_ALPHA_TEST);//Begin Alpha Test
    glBegin(GL_POLYGON);

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

    //Rightside up, Facing Right way
    glTexCoord2f(0.0f, 0.0f); glVertex2d(0, 480);
    glTexCoord2f(0.0f, 1.0f); glVertex2d(0, 0);
    glTexCoord2f(1.0f, 1.0f); glVertex2d(640, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex2d(640,480);
    glEnd();

    glDisable(GL_ALPHA_TEST);//End Alpha Test
    glDisable(GL_TEXTURE_2D);//Disabe Texture

    glutSwapBuffers();

}

//---------------------------------------------------------------------------------------------------
//　　Mouse
//　　Desc : マウス処理
//---------------------------------------------------------------------------------------------------
void Mouse(int button, int state, int x, int y)
{
	switch ( button )
	{
	case GLUT_LEFT_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_MIDDLE_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	case GLUT_RIGHT_BUTTON:
		switch ( state )
		{
		case GLUT_DOWN:
			break;

		case GLUT_UP:
			break;
		}
		break;

	default:
		break;
	}
	

}

//--------------------------------------------------------------------------------------------------
//　　Motion
//　　Desc : マウスドラッグ時
//-------------------------------------------------------------------------------------------------
void Motion(int x, int y)
{
}

//--------------------------------------------------------------------------------------------------
//　　PassiveMotion
//　　Desc : マウス移動時
//--------------------------------------------------------------------------------------------------
void PassiveMotion(int x, int y)
{
}

//--------------------------------------------------------------------------------------------------
//　　Keyboard
//　　Desc : キーボード処理
//--------------------------------------------------------------------------------------------------
void Keyboard(unsigned char key, int x, int y)
{
	switch ( key )
	{
	case '\033':
		exit(0);
		break;

	default:
		break;
	}
}

//--------------------------------------------------------------------------------------------------
//　　Special
//　　Desc : 特殊キー処理
//--------------------------------------------------------------------------------------------------
void Special(int key, int x, int y)
{

}
