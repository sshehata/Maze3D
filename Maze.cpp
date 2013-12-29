#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>
#include "Maze.h"

#define cell(r,c) ((r)*m_cols + (c))

using std::cout;
using std::endl;

Maze::Maze(int rows, int cols)
{
	m_verticalEdges = m_horizontalEdges = NULL;
	m_rows = rows;
	m_cols = cols;
	m_exit = 0;
}

void Maze::Generate()
{
	m_horizontalEdges = new bool[(m_rows+1) * m_cols];
	m_verticalEdges = new bool[m_rows * (m_cols+1)];
	bool* visited = new bool[m_rows * m_cols];

	for (int i = 0; i < (m_rows+1) * m_cols; i++)
		m_horizontalEdges[i] = true;
	for (int i = 0; i < m_rows * (m_cols+1); i++)
		m_verticalEdges[i] = true;
	for (int i = 0; i < m_rows * m_cols; i++)
		visited[i] = false;

	srand(time(NULL));
	int exitBorder = rand() % 4;
	int exit = 0;
	switch (exitBorder)
	{
	case NORTH:
		exit = rand() % m_cols;
		m_horizontalEdges[cell(0, exit)] = false;
		GenerateHelper(0, exit, visited);
		break;
	case SOUTH:
		exit = rand() % m_cols;
		m_horizontalEdges[cell(m_rows, exit)] = false;
		GenerateHelper(m_rows-1, exit, visited);
		break;
	case EAST:
		exit = rand() % m_rows;
		m_verticalEdges[cell(exit, m_cols)] = false;
		GenerateHelper(exit, m_cols-1, visited);
		break;
	case WEST:
		exit = rand() % m_rows;
		m_verticalEdges[cell(exit, 0)] = false;
		GenerateHelper(exit, 0, visited);
		break;
	default:
		break;
	}
	
	for (int i = 0; i < m_rows * (m_cols+1); i++)
		bool b = m_verticalEdges[i];

	delete [] visited;
}

void Maze::GenerateHelper(int row, int col, bool* visisted)
{
	if (isValid(row, col) && !visisted[cell(row, col)])
	{
		visisted[cell(row, col)] = true;

		int directions [] = {0,1,2,3};
		std::random_shuffle(std::begin(directions), std::end(directions));

		int nextCol = 0, nextRow =  0;
		for (int i = 0; i < 4; i++)
		{
			switch (directions[i])
			{
			case NORTH:
				if (isValid(row-1, col) && !visisted[cell(row-1, col)])
				{
					m_horizontalEdges[cell(row, col)] = false;
					GenerateHelper(row-1, col, visisted);
				}
				break;
			case SOUTH:
				if (isValid(row+1, col) && !visisted[cell(row+1, col)])
				{
					m_horizontalEdges[cell(row+1, col)] = false;
					GenerateHelper(row+1, col, visisted);
				}
				break;
			case EAST:
				if (isValid(row, col+1) && !visisted[cell(row, col+1)])
				{
					m_verticalEdges[cell(row, col+1)] = false;
					GenerateHelper(row, col+1, visisted);
				}
				break;
			case WEST:
				if (isValid(row, col-1) && !visisted[cell(row, col-1)])
				{
					m_verticalEdges[cell(row, col)] = false;
					GenerateHelper(row, col-1, visisted);
				}
				break;
			default:
				continue;
			}
		}
	}
}

bool Maze::IsWall(int row, int col, Direction direction)
{
	switch (direction)
	{
	case NORTH:
		return m_horizontalEdges[cell(row,col)];
	case SOUTH:
		return m_horizontalEdges[cell(row+1,col)];
	case EAST:
		return m_verticalEdges[cell(row, col+1)];
	case WEST:
		return m_verticalEdges[cell(row,col)];
	default:
		return false;
	}
}

void Maze::Render2D()
{
	for (int i = 0; i < m_rows; i++)
		cout << (IsWall(0, i, NORTH) ? " _" : "  ");
	cout << endl;
	
	for (int i  = 0; i < m_rows; i++) 
	{
		for (int j = 0; j < m_cols; j++) 
		{
			cout << (IsWall(i, j, WEST) ? "|" : " ");
			cout << (IsWall(i, j, SOUTH) ? "_" : " ");
		}
		cout << (IsWall(i, m_cols-1, EAST) ? "|" : " ");
		cout << endl;
	}
	cout << endl;
}
