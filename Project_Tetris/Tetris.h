#pragma once

#include "Game.h"

class CTetris
{
public:
	static CGame game;
	static void mainSleep();
	static void clearConsole();
	static void waitPUSH();
private:
};