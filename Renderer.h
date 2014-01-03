#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Maze.h"

#define scale 2
#define MAZE_WIDTH 10
#define MAZE_HEIGHT 10

enum Orientation{
	VERTICAL,
	HORIZONTAL
};

void RenderWall(Orientation);
void PreRender();
void Render();
void SetLighting();
void InitRenderer();
void LoadGLTextures();
void Idle();

extern bool falling;
extern Maze maze;

#endif