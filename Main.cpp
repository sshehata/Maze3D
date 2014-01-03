#include <Windows.h>
#include <glut.h>
#include "Renderer.h"
#include "Controller.h"

using namespace std;

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_SINGLE);
	glutInitWindowSize(1200, 1000);
	glutInitWindowPosition(100, 50);
	glutCreateWindow("Maze3D");
	glutDisplayFunc(Render);
	glutKeyboardFunc(Move);
	glutIdleFunc(Idle);
	InitRenderer();
	InitController();
	glutMainLoop();
}

