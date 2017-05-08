#pragma once

#include "Field.h"

class CFigure
{
public:
	CFigure(int x_c, int y_c, int size_c, int index_c, int matrix_c[4][4]);
	int x;
	int y;
	int index;
	int matrix[4][4];
	int r;
	int getX();
	int getY();
	int size;
	void up();
	void right(CField &field);
	void left(CField &field);
	void down();
	void downMax(CField &field);
	void upMax(CField &field);
	void leftMax(CField &field);
	void rotate(CField &field);
	void countRotate(int count);
	void land(CField &field);
	void moveToAngle(CField &field);
	bool isCurrentPos(CField &field);
	bool isMaxRight(CField &field);
private:
};