#pragma once

class CField
{
public:
	CField(int width_c, int height_c);
	int width;
	int height;
	int matrix[20][10];
	int getWidth();
	int getHeight();
	int addScore(int countLine);
	int getValue(int x, int y);
	void setValue(int x, int y, int value);
	void clearField();
	int remove();
	int countHeight();
	int countLines();
	int countHoles();
	int countMonoton();
private:
};
