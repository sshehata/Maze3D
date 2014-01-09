#include <cstdlib>
#include <string>
#include <glut.h>
#include "SOIL.h"
#include "Renderer.h"
#include "Controller.h"
#include "Maze.h"

#pragma comment(lib, "SOIL")

using std::string;

// Rendering Initialization

Maze maze(MAZE_WIDTH, MAZE_HEIGHT);
unsigned int textures[3];
double timestamp = 0;
double timestamp2 = 0;

void InitRenderer()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);       
	glClearColor(0.0,0.0,0.0,0.0);
	
	LoadGLTextures();
	SetLighting();

	maze.Generate();
	maze.Render2D();
}

void LoadGLTextures()
{
	textures[0] = SOIL_load_OGL_texture("ground.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	textures[1] = SOIL_load_OGL_texture("maze.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
	textures[2] = SOIL_load_OGL_texture("pad.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void SetLighting()
{
	GLfloat lightIntensity[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat light_position[]={7.0f,6.0f,3.0f,0.0f}; 
	glLightfv(GL_LIGHT0,GL_POSITION,lightIntensity); 
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);

	GLfloat lmodel_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_FALSE);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE) ;
}

double intens = 2;
void SetDynamicLighting()
{
	GLfloat lightIntensity1[]={intens,0,0,1.0f};
	GLfloat light_position1[]={maze.GetExitCol()*scale + scale/2,2,maze.GetExitRow()*scale + scale/2,1.0f}; 
	GLfloat spotLight[] = {0,-2,0};
	glLightfv(GL_LIGHT1,GL_POSITION,light_position1); 
	glLightfv(GL_LIGHT1,GL_SPECULAR,lightIntensity1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightIntensity1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0);
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,spotLight);
}

// Rendering

void PreRender()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1200.0/1000.0, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);       
	glEnable(GL_LIGHTING);
	gluLookAt(position.xPosition, scale/2, position.zPosition,
			  position.xTarget,  scale/2, position.zTarget,
			  0, 1, 0
			  );
	SetDynamicLighting();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderSolidCube()
{
	static GLfloat n[6][3] =
	{
		{-1.0, 0.0, 0.0},
		{0.0, 1.0, 0.0},
		{1.0, 0.0, 0.0},
		{0.0, -1.0, 0.0},
		{0.0, 0.0, 1.0},
		{0.0, 0.0, -1.0}
	};
	static GLint faces[6][4] =
	{
		{0, 1, 2, 3},
		{3, 2, 6, 7},
		{7, 6, 5, 4},
		{4, 5, 1, 0},
		{5, 6, 2, 1},
		{7, 4, 0, 3}
	}; 

	GLfloat v[8][3];

	v[0][0] = v[1][0] = v[2][0] = v[3][0] = -0.5;
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = 0.5;
	v[0][1] = v[1][1] = v[4][1] = v[5][1] = -0.5;
	v[2][1] = v[3][1] = v[6][1] = v[7][1] = 0.5;
	v[0][2] = v[3][2] = v[4][2] = v[7][2] = -0.5;
	v[1][2] = v[2][2] = v[5][2] = v[6][2] = 0.5;

	for (int i = 5; i >= 0; i--) 
	{
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glTexCoord2f(0,0);
		glVertex3fv(&v[faces[i][0]][0]);
		glTexCoord2f(0,1);
		glVertex3fv(&v[faces[i][1]][0]);
		glTexCoord2f(1,1);
		glVertex3fv(&v[faces[i][2]][0]);
		glTexCoord2f(1,0);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void RenderWall(Orientation o, int x = 0, int z = 0, double y = 0)
{
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPushMatrix();
	glTranslated(x, y, z);
	if (o == HORIZONTAL)
	{
		glTranslated(scale/2.0,scale/2.0,0);
		glScaled(scale,scale,0.1);
	}
	else
	{
		glTranslated(0,scale/2.0,scale/2.0);
		glScaled(0.1,scale,scale);
	}
	RenderSolidCube();
	glPopMatrix();
}

void RenderFloor(int i, int j)
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2d(0,0);
	glVertex3d(i,0,j);
	glTexCoord2d(0,1);
	glVertex3d(i,0,j+scale);
	glTexCoord2d(1,1);
	glVertex3d(i+scale,0,j+scale);
	glTexCoord2d(1,0);
	glVertex3d(i+scale,0,j);
	glEnd();
}

double mazeHeight = -scale;
void RenderMaze()
{
	for (int i = 0; i < maze.Height(); i++)
	{
		for (int j = 0; j < maze.Width(); j++)
		{
			if (maze.IsWall(i, j, NORTH))
				RenderWall(HORIZONTAL, j*scale, i*scale, mazeHeight);
			if (maze.IsWall(i, j, WEST))
				RenderWall(VERTICAL, j*scale, i*scale, mazeHeight);
			RenderFloor(i*scale, j*scale);

		}
		if (maze.IsWall(i, maze.Width()-1, EAST))
			RenderWall(VERTICAL, maze.Width()*scale, i*scale, mazeHeight);
	}
	for (int i = 0; i < maze.Width(); i++)
		if (maze.IsWall(maze.Height()-1, i, SOUTH))
			RenderWall(HORIZONTAL, i*scale, maze.Height()*scale, mazeHeight);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderWinPad()
{
	// texture
	glBindTexture(GL_TEXTURE_2D, textures[2]);

	int exitCol = maze.GetExitCol();
	int exitRow = maze.GetExitRow();

	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(exitCol * scale, 0.1, exitRow*scale);
	glTexCoord2d(0,1);
	glVertex3d((exitCol + 1) * scale,0.1, exitRow * scale);
	glTexCoord2d(1,0);
	glVertex3d((exitCol + 1) * scale,0.1,(exitRow + 1) * scale);
	glTexCoord2d(1,1);
	glVertex3d(exitCol * scale,0.1,(exitRow + 1) * scale);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
}

string toString(int number)
{
	char buffer[21];
	return itoa(number, buffer, 10);
}

void RenderText()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	gluOrtho2D(0.0, 1200.0, 0.0, 1000.0);
	
	string s = "Time: ";
	string time = s + toString(seconds);
	glPushMatrix();
	glTranslated(100, 900, 0);
	glColor3d(0.7,0.7,0.7);
	glScaled(0.15, 0.15, 0.15);
	for (int i = 0; i < time.length(); i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, time[i]);
	glPopMatrix();
	
	glTranslated(600, 900,0);
	glScaled(0.2,0.2,0.2);
	if (state == WIN) {
		glColor3f(0.0f, 1.0f, 0.0f);
			
		for (char *p = "you win"; *p; p++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
		string s = "You Scored: ";
		string sScore = s + toString(score);
		glTranslated(-700, -200,0);
		for (int i = 0; i < sScore.length(); i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, sScore[i]);
	}
	else if (state == LOSE)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		for (char *p = "you lose"; *p; p++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}
}

void RenderFloor(int i, int j, int size)
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2d(0,0);
	glVertex3d(i,-0.01,j);
	glTexCoord2d(0,1);
	glVertex3d(i,-0.01,j+size);
	glTexCoord2d(1,1);
	glVertex3d(i+size,-0.01,j+size);
	glTexCoord2d(1,0);
	glVertex3d(i+size,-0.01,j);
	glEnd();
}

void Render()
{
	double mseconds = glutGet(GLUT_ELAPSED_TIME) - timestamp2;
	if (mseconds >= 10)
	{
		PreRender();
		RenderMaze();
		RenderFloor(-10, -10, 100);
		RenderText();
		glFlush();
		timestamp2 += mseconds;
	}
}

// Idle Function

bool raising  = true;
bool falling = false;
double deltaIntens = 10;

void Idle()
{
	double mseconds = glutGet(GLUT_ELAPSED_TIME) - timestamp;
	if ((int)mseconds % 50 == 0 (raising || falling))
	{
		if (raising && mazeHeight < 0)
			mazeHeight += scale/100000.0;
		else if (raising)
			raising = false;
		else if (falling && mazeHeight >= -scale)
			mazeHeight -= scale/100000.0;
		else if (falling)
			falling = false;
		glutPostRedisplay();

	}

	if (mseconds >= 1000 && state == PLAY)
	{
			seconds--;
			if (seconds <= 0)
				state = LOSE;

		glutPostRedisplay();
		timestamp += mseconds;
	}
}
