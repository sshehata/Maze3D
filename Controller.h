#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

void Move(unsigned char, int, int);
void InitController();
void Look(int, int);

enum GameState{
	PLAY,
	WIN,
	LOSE
};

struct PlayerPosition{
	double xPosition;
	double zPosition;
	double xTarget;
	double zTarget;
	double angle;
};

extern PlayerPosition position;
extern GameState state;
extern int seconds;
extern double score;

#endif
