#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

void Move(unsigned char, int, int);
void InitController();

struct PlayerPosition{
	double xPosition;
	double zPosition;
	double xTarget;
	double zTarget;
	double angle;
};

extern PlayerPosition position;

#endif
