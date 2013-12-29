#include <Windows.h>
#include <glut.h>
#include "Renderer.h"

int main(int argc, char** argv){
glutInit(&argc, argv); 
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
glutInitWindowSize(640,480);
glutInitWindowPosition(200, 150);
glutCreateWindow("3D Maze");
Init();
glutDisplayFunc(Render);
glutKeyboardFunc(Controller);
glutMainLoop();
}
