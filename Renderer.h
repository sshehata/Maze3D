#ifndef __RENDERER_H__
#define __RENDERER_H__

enum Orientation{
	VERTICAL,
	HORIZONTAL
};

void Controller(unsigned char, int, int);
void DrawWall(Orientation);
void PreRender();
void Render();
void SetLighting();
void Init();

#endif