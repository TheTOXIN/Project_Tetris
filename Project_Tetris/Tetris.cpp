#include "stdafx.h"
#include "Tetris.h"
#include "conio.h"
#include "iostream"

CGame CTetris::game(10, 20);

void CTetris::clearConsole()
{
	system("cls");
}

void CTetris::waitPUSH()
{
	std::cout << "Press any button..." << std::endl;
	if (_getch())
	{
		Sleep(10);
	}
}

void CTetris::mainSleep()
{
	Sleep(100);
}
