#pragma once

#include "Factory.h"
#include "Printer.h"
#include "AI.h"
#include "Player.h"
#include "WindowView.h"
#include "KeyController.h"
#include "MediaPlayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

class CGame
{
public:
	CGame(int width, int height);
	bool isPause;
	float setTEMP;
	float temp;
	int gameMode;
	int windowMode;
	int listMode;
	RenderWindow window;
	Clock clock;
	CComputer computer;
	CPlayer player1;
	CPlayer player2;
	CFactory factory;
	CPrinter printer;
	CWindowView wv;
	CKeyController kc;
	void start();
	void menuUpdate();
	void listUpdate();
	void gameUpdate();
	void tickTack();
	void updateTmp(int score);
private:
};
