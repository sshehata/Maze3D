#include <Windows.h>
#include "Maze.h"

using namespace std;

int main()
{
	Maze maze(35,35);
	maze.Generate();
	maze.Render2D();
	
	
	system("PAUSE");
}

