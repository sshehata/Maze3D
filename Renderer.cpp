#include <glut.h>
#include "Renderer.h"

void DrawWall(Orientation o)
{
	glPushMatrix();
	if (o == HORIZONTAL)
	{
		glTranslated(0.5,0.5,0);
		glScaled(1,1,0.1);
	}
	else
	{
		glTranslated(0,0.5,0.5);
		glScaled(0.1,1,1);
	}
	glutSolidCube(1);
	glPopMatrix();
}

void Init()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glClearColor(1.0,1.0,1.0,0.0);
}

void SetLighting()
{
	GLfloat lightIntensity[]={0.7f,0.7f,1,1.0f};
	GLfloat light_position[]={7.0f,6.0f,3.0f,0.0f}; 
	glLightfv(GL_LIGHT0,GL_POSITION,lightIntensity); 
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightIntensity);
}

void PreRender()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	double winHt=1.0;
	gluPerspective(45.0,640.0/480.0,1.0,100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(-.5, 1, -1,0,0.0,4.0,0,1.0,0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Controller(unsigned char key, int x, int y)
{

}

void Render()
{
	SetLighting();
	PreRender();

	DrawWall(HORIZONTAL);
	DrawWall(VERTICAL);
	glTranslated(-1,0,0);
	DrawWall(VERTICAL);
	glTranslated(0,0,1);
	DrawWall(VERTICAL);

	glFlush();
}