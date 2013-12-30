#include <string>
#include <glut.h>
#include "SOIL.h"
#include "Renderer.h"
#include "Controller.h"
#include "Maze.h"

#pragma comment(lib, "SOIL")

// Rendering Initialization

Maze maze(10, 10);
unsigned int textures[2];

void InitRenderer()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
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
 
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}

void SetLighting()
{
	GLfloat lightIntensity[]={1.0f,1.0f,1.0f,1.0f};
	GLfloat light_position[]={7.0f,6.0f,3.0f,0.0f}; 
	glLightfv(GL_LIGHT0,GL_POSITION,light_position); 
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
}

// Rendering

void PreRender()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1200.0/1000.0, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(position.xPosition, scale/2, position.zPosition,
			  position.xTarget,   scale/2, position.zTarget,
			  0, 1, 0
			  );
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

void RenderWall(Orientation o, int x = 0, int z = 0)
{
	glPushMatrix();
	glTranslated(x, 0, z);
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

void RenderMaze()
{
	glBindTexture(GL_TEXTURE_2D, textures[1]);

	for (int i = 0; i < maze.Height(); i++)
	{
		for (int j = 0; j < maze.Width(); j++)
		{
			if (maze.IsWall(i, j, NORTH))
				RenderWall(HORIZONTAL, j*scale, i*scale);
			if (maze.IsWall(i, j, WEST))
				RenderWall(VERTICAL, j*scale, i*scale);
		}
		if (maze.IsWall(i, maze.Width()-1, EAST))
			RenderWall(VERTICAL, maze.Width()*scale, i*scale);
	}
	for (int i = 0; i < maze.Width(); i++)
		if (maze.IsWall(maze.Height()-1, i, SOUTH))
			RenderWall(HORIZONTAL, i*scale, maze.Height()*scale);
}

void RenderFloor()
{
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(0,0,0);
	glTexCoord2d(0,1);
	glVertex3d(0,0,20);
	glTexCoord2d(1,1);
	glVertex3d(20,0,20);
	glTexCoord2d(1,0);
	glVertex3d(20,0,0);
	glEnd();
}

void Render()
{
		PreRender();
		RenderFloor();
		RenderMaze();
		glColor3d(1.0,1.0,1.0);
		glFlush();
}
