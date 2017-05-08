#pragma once
#include "Figure.h"

class CFactory
{
public:
	static int brick_1[4][4];
	static int brick_2[4][4];
	static int brick_3[4][4];
	static int brick_4[4][4];
	static int brick_5[4][4];
	static int brick_6[4][4];
	static int brick_7[4][4];
	int space[4][4];
	CFigure createFigure();
	CFigure maker(int size, int index, int brick[4][4]);
private:
};