#ifndef __RENDERER_H__
#define __RENDERER_H__

#include "Maze.h"

#define scale 2

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

extern Maze maze;

#endif