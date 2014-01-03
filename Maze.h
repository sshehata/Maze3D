#ifndef __MAZE_H__
#define __MAZE_H__

enum Direction{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

class Maze{
private:
	bool* m_verticalEdges;
	bool* m_horizontalEdges;
	int m_rows;
	int m_cols;
	int m_exitRow;
	int m_exitCol;

	void GenerateHelper(int, int, bool*);
	inline bool isValid(int row, int col) { return row >= 0 && row < m_rows && col >= 0 && col < m_cols; }

public:
	Maze(int rows, int cols);
	void Generate();
	bool IsWall(int row, int col, Direction direction);
	void Render2D();
	int Width() {return m_cols;}
	int Height() {return m_rows;}
	int GetExitCol() {return m_exitCol;}
	int GetExitRow() {return m_exitRow;}
};

#endif