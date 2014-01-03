#include <glut.h>
#include <cmath>
#include "Renderer.h"
#include "Controller.h"

PlayerPosition position;
GameState state;
int seconds;
double score;

void InitController()
{
	/*position.xPosition = MAZE_WIDTH - maze.GetExitCol() + 1;
	position.xTarget = MAZE_WIDTH - maze.GetExitCol() + 1;
	position.zPosition = MAZE_HEIGHT - maze.GetExitRow() + 1;
	position.zTarget = MAZE_HEIGHT - maze.GetExitRow() + 2;
	position.angle = 3.14/2.0f;*/

	position.xPosition = MAZE_WIDTH+1;
	position.zPosition = MAZE_HEIGHT+1;
	position.xTarget = MAZE_WIDTH+1;
	position.zTarget = MAZE_HEIGHT+1;
	state = PLAY;
	seconds = MAZE_WIDTH * MAZE_HEIGHT * 4;
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

	return false;
}

void isWin()
{
	int row =  (int) position.zPosition/scale;
	int col = (int) position.xPosition/scale;
	if (row == maze.GetExitRow() && col == maze.GetExitCol()) {
		score = seconds * log(MAZE_WIDTH * MAZE_HEIGHT);
		state = WIN;
		falling = true;
	}
}

void Move(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 'w':
		if (!isCollision(VERTICAL, position.xPosition + 0.1 + 0.1*cos(position.angle), position.zPosition + 0.1 + 0.1*sin(position.angle))
			&& !isCollision(VERTICAL, position.xPosition - 0.1 + 0.1*cos(position.angle), position.zPosition - 0.1 + 0.1*sin(position.angle))
			&& state == PLAY)
		{
			position.zPosition += 0.1*sin(position.angle);
			position.zTarget += 0.1*sin(position.angle);
			position.xPosition += 0.1*cos(position.angle);
			position.xTarget += 0.1*cos(position.angle);
		}
		break;
	case 's':
		if (!isCollision(VERTICAL, position.xPosition + 0.1 - 0.1*cos(position.angle), position.zPosition + 0.1 - 0.1*sin(position.angle))
			&& !isCollision(VERTICAL, position.xPosition - 0.1 - 0.1*cos(position.angle), position.zPosition - 0.1 - 0.1*sin(position.angle))
			&& state == PLAY)
		{
			position.zPosition -= 0.1*sin(position.angle);
			position.zTarget -= 0.1*sin(position.angle);
			position.xPosition -= 0.1*cos(position.angle);
			position.xTarget -= 0.1*cos(position.angle);
		}
		break;
	case 'a':
		position.angle -= 0.1;
		position.zTarget = sin(position.angle) + position.zPosition;
		position.xTarget = cos(position.angle) + position.xPosition;
		break;
	case 'd':
		position.angle += 0.1;
		position.zTarget = sin(position.angle) + position.zPosition;
		position.xTarget = cos(position.angle) + position.xPosition;
		break;
	default:
		break;
	}
	isWin();
	glutPostRedisplay();
}