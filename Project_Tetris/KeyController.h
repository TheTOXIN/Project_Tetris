#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "WindowView.h"
#include "KeyController.h"
#include "MediaPlayer.h"
#include "AI.h"
#include "Player.h"

using namespace sf;

class CKeyController
{
public:
	void keyMenu(RenderWindow & window, CWindowView & wv);
	void keyList(RenderWindow & window, CWindowView & wv);
	void keyGame(RenderWindow & window, CWindowView & wv);
	bool checkClick(Sprite & sprite, RenderWindow & window, CWindowView & wv, FloatRect rect);
	void playerControl(RenderWindow & window, CPlayer &player1, CPlayer &player2);
	void exit();
private:
};
