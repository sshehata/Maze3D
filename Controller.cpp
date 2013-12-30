#include <glut.h>
#include "Renderer.h"
#include "Controller.h"

PlayerPosition position;

void InitController()
{
	position.xPosition = 1.0f;
	position.xTarget = 1.0f;
	position.zPosition = 1.0f;
	position.zTarget = 2.0f;
	position.angle = 90.0f;
}

bool isCollision(Orientation o, double x, double z)
{
	int row =  (int) z/scale;
	int col = (int) x/scale;
	bool collision = false;
	const float padding = 0.2f;
	
	double cellPosition = z - scale * row;
	if (cellPosition >= scale/2.0)
		collision = maze.IsWall(row, col, SOUTH) && (scale - cellPosition < padding);
	else
		collision = maze.IsWall(row, col, NORTH) && (cellPosition < padding);
	
	cellPosition = x - scale * col;
	if (cellPosition >= scale/2.0)
		collision = collision || (maze.IsWall(row, col, EAST) && (scale - cellPosition < padding));
	else
		collision = collision || (maze.IsWall(row, col, WEST) && (cellPosition < padding));

	return collision;
}

void Move(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		if (!isCollision(VERTICAL, position.xPosition + 0.1, position.zPosition + 0.2)
			&& !isCollision(VERTICAL, position.xPosition - 0.1, position.zPosition))
		{
			position.zPosition += 0.1;
			position.zTarget += 0.1;
		}
		break;
	case 's':
		if (!isCollision(VERTICAL, position.xPosition + 0.1, position.zPosition)
			&& !isCollision(VERTICAL, position.xPosition - 0.1, position.zPosition - 0.2))
		{
			position.zPosition -= 0.1;
			position.zTarget -= 0.1;
		}
		break;
	case 'a':
		position.xPosition += 0.1;
		position.xTarget += 0.1;
		break;
	case 'd':
		position.xPosition -= 0.1;
		position.xTarget -= 0.1;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}