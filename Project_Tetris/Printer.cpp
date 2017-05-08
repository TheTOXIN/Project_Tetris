#include "stdafx.h"
#include "Printer.h"
#include "Figure.h"
#include "Field.h"
#include "Tetris.h"
#include "iostream"

using namespace std;

CPrinter::CPrinter()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = 0;
	position.Y = 0;
}

void CPrinter::print(CField &field, CFigure &figure, CFigure &nextFigure, int pos, int score)
{
	position.X = pos;
	position.Y = 0;

	int canvas[20][10];

	for (int i = 0; i < field.getHeight(); i++)
	{
		for (int j = 0; j < field.getWidth(); j++)
		{
			canvas[i][j] = field.matrix[i][j];
		}
	}

	int left = figure.getX();
	int top = figure.getY();

	for (int i = 0; i < figure.size; i++)
	{
		for (int j = 0; j < figure.size; j++)
		{
			if (top + i >= field.getHeight() || left + j >= field.getWidth()) continue;
			if (figure.matrix[i][j] == 1)
			{
				canvas[top + i][left + j] = figure.index;
			}
		}
	}

	SetConsoleCursorPosition(hConsole, position);
	cout << "--------------------------------" << endl;
	position.Y++;
	SetConsoleCursorPosition(hConsole, position);
	for (int i = 0; i < field.getHeight(); i++)
	{
		cout << "|";
		for (int j = 0; j < field.getWidth(); j++)
		{
			int index = canvas[i][j];
			if (index == 0)
				cout << "   ";
			else if (index >= 1 && index <= 7)
				cout << "[" << index << "]";
			else
				cout << "???";
		}
		cout << "|";
		cout << endl;
		position.Y++;
		SetConsoleCursorPosition(hConsole, position);
	}
	cout << "--------------------------------" << endl;

	position.Y++;
	SetConsoleCursorPosition(hConsole, position);
	cout << "<==============" << score << "==============>" << endl;
	position.Y++;

	SetConsoleCursorPosition(hConsole, position);
	cout << "NEXT_FIGURE" << endl;
	position.Y++;
	SetConsoleCursorPosition(hConsole, position);
	for (int i = 0; i < 4; i++) {
		cout << '|';
		for (int j = 0; j < 4; j++) {
			if (nextFigure.matrix[i][j] == 1)
				cout << "[ ]";
			else
				cout << "   ";
		}
		cout << '|' << endl;
		position.Y++;
		SetConsoleCursorPosition(hConsole, position);
	}
}