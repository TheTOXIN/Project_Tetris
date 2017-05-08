#include "stdafx.h"
#include "Figure.h"
#include "Tetris.h"

CFigure::CFigure(int x_c, int y_c, int size_c, int index_c, int matrix_c[4][4])
{
	x = x_c;
	y = y_c;
	size = size_c;
	index = index_c;
	r = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) 
		{
			matrix[i][j] = matrix_c[i][j];
		}
	}
}

int CFigure::getX()
{
	return x;
}

int CFigure::getY()
{
	return y;
}

void CFigure::up()
{
	y--;
}

void CFigure::right(CField &field)
{
	x++;
	if (!isCurrentPos(field))
		x--;
}

void CFigure::left(CField &field)
{
	x--;
	if (!isCurrentPos(field))
		x++;
}

void CFigure::down()
{
	y++;
}

void CFigure::downMax(CField &field)
{
	while (isCurrentPos(field))
		y++;
	y--;
}

void CFigure::upMax(CField & field)
{
	while (isCurrentPos(field))
		y--;
	y++;
}

void CFigure::leftMax(CField & field)
{
	while (isCurrentPos(field))
		x--;
	x++;
}

void CFigure::rotate(CField &field)
{
	r++;
	int tmp[4][4];
	
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			tmp[i][j] = matrix[i][j];
		}
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			matrix[j][size - 1 - i] = tmp[i][j];
		}
	}

	if (!isCurrentPos(field))
	{
		r--;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++) 
			{
				matrix[i][j] = tmp[i][j];
			}
		}
	}
}

void CFigure::countRotate(int count)
{
	int tmp[4][4];

	for (int k = 0; k < count; k++) 
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				tmp[i][j] = matrix[i][j];
			}
		}

		for (int i = 0; i < size; ++i)
		{
			for (int j = 0; j < size; ++j) 
			{
				matrix[j][size - 1 - i] = tmp[i][j];
			}
		}
	}
}

void CFigure::land(CField &field)
{
	if (isCurrentPos(field))
	{
		for (int i = 0; i < size; i++) 
		{
			for (int j = 0; j < size; j++) 
			{
				if (matrix[i][j] == 1) 
				{
					field.matrix[i + y][j + x] = index;
				}
			}
		}
	}
}

void CFigure::moveToAngle(CField & field)
{
	upMax(field);
	leftMax(field);
}

bool CFigure::isCurrentPos(CField &field)
{
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 1)
			{
				if (y + i >= field.getHeight() || y + i < 0) return false;
				if (field.matrix[i + y][x + j] >= 1 && field.matrix[i + y][x + j] <= 7) return false;
				if (x+j < 0 || x+j > field.getWidth()-1) return false;
			}
		}
	}
	return true;
}

bool CFigure::isMaxRight(CField & field)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (matrix[i][j] == 1)
			{
				if (x + j < 0 || x + j > field.getWidth() - 1) return false;
			}
		}
	}
	return true;
}
