#ifndef __RENDERER_H__
#define __RENDERER_H__

#define scale 2

enum Orientation{
	VERTICAL,
	HORIZONTAL
};

void Controller(unsigned char, int, int);
void RenderWall(Orientation);
void PreRender();
void Render();
void SetLighting();
void Init();
void LoadGLTextures();

#endif