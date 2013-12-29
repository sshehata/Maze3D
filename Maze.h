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
	int m_exit;

	void GenerateHelper(int, int, bool*);
	inline bool isValid(int row, int col) { return row > 0 && row < m_rows && col > 0 && cols < m_cols; }

public:
	Maze(int rows, int cols);
	void Generate();
	void IsWall(int row, int col, Direction direction);
};

#endif