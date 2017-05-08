#pragma once

#include "Field.h"
#include "Figure.h"
#include "windows.h"

class CPrinter
{
public:
	CPrinter();
	void print(CField &field, CFigure &figure, CFigure &nextFigrue, int pos, int score);
	COORD position;
	HANDLE hConsole;
private:
};
