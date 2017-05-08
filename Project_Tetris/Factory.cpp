#include "stdafx.h"
#include "Factory.h"
#include "Figure.h"
#include "iostream"

using namespace std;

int CFactory::brick_1[4][4] = {
	{ 0, 0, 1 },
	{ 0, 1, 1 },
	{ 0, 1, 0 },
};

int CFactory::brick_2[4][4] = {
	{ 1, 0, 0 },
	{ 1, 1, 0 },
	{ 0, 1, 0 },
};

int CFactory::brick_3[4][4] = {
	{ 1, 1 },
	{ 1, 1 },
};

int CFactory::brick_4[4][4] = {
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 0, 0 },
};

int CFactory::brick_5[4][4] = {
	{ 0, 1, 0 },
	{ 1, 1, 1 },
	{ 0, 0, 0 },
};

int CFactory::brick_6[4][4] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 1, 1, 0 },
};

int CFactory::brick_7[4][4] = {
	{ 0, 1, 0 },
	{ 0, 1, 0 },
	{ 0, 1, 1 },
};

CFigure CFactory::createFigure()
{
	int index = rand() % 7;
	
	switch (index)
	{
	case 0: return maker(3, 1, brick_1); break;
	case 1: return maker(3, 2, brick_2); break;
	case 2: return maker(2, 3, brick_3); break;
	case 3: return maker(4, 4, brick_4); break;
	case 4: return maker(3, 5, brick_5); break;
	case 5: return maker(3, 6, brick_6); break;
	case 6: return maker(3, 7, brick_7); break;
	}
}

CFigure CFactory::maker(int size, int index, int brick[4][4])
{
	CFigure figure(10 / 2, 0, size, index, brick);
	figure.countRotate(rand() % 4);
	return figure;
}
