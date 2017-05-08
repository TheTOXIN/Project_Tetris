#include "stdafx.h"
#include "Game.h"
#include "Tetris.h"
#include "Field.h"
#include "MediaPlayer.h"

CField::CField(int width_c, int height_c)
{
	width = width_c;
	height = height_c;
}

int CField::getWidth()
{
	return width;
}

int CField::getHeight()
{
	return height;
}

int CField::addScore(int countLine)
{
	int score = 0;
	if (countLine == 1)
		score += 100;
	else if (countLine == 2)
		score += 300;
	else if (countLine == 3)
		score += 700;
	else if (countLine == 4)
		score += 1500;
	return score;
}

int CField::getValue(int x, int y)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		return matrix[y][x];
}

void CField::setValue(int x, int y, int value)
{
	if (x >= 0 && x < width && y >= 0 && y < height)
		matrix[y][x] = value;
}

void CField::clearField()
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (matrix[i][j] != 0)
			{
				matrix[i][j] = 0;
			}
		}
	}
}

int CField::remove()
{
	int countLine = 0;
	for (int i = 0; i < height; i++)
	{
		int count = 0;
		for (int j = 0; j < width; j++) 
		{
			if (matrix[i][j] != 0)
				count++;
		}

		if (count == width) 
		{
			countLine++;
			for (int j = 0; j < width; j++) 
			{
				matrix[i][j] = 0;
			}

			for (int j = i; j > 0; j--)
			{
				for (int k = 0; k < width; k++)
				{
					matrix[j][k] = matrix[j - 1][k];
				}
			}
		}
	}
	return addScore(countLine);
}

int CField::countHeight()
{
	int count = 0;
	for (int i = 0; i < width; i++)
	{
		int j = 0;
		while (matrix[j][i] == 0 && j < height)
			j++;
		count += height - j;
	}
	return count;
}

int CField::countLines()
{
	int countLine = 0;
	for (int i = 0; i < height; i++)
	{
		int countB = 0;
		for (int j = 0; j < width; j++)
		{
			if (matrix[i][j] != 0)
				countB++;
		}

		if (countB == width) 
		{
			countLine++;
		}
	}
	return countLine;
}

int CField::countHoles()
{
	int count = 0;

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			if (matrix[j][i] != 0)
			{
				while (j < height)
				{
					if (matrix[j][i] == 0)
						count++;
					j++;
				}
			}
		}
	}
	return count;
}

int CField::countMonoton()
{
	int count = 0;
	int mas[10];
	for (int i = 0; i < width; i++)
	{
		int j = 0;
		while (matrix[j][i] == 0 && j < height)
			j++;
		mas[i] = height - j;
	}
	for (int i = 0; i < width-1; i++)
	{
		count += abs(mas[i] - mas[i + 1]);
	}
	return count;
}
