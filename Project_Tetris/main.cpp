#include "stdafx.h"
#include "windows.h"
#include "iostream"
#include "Game.h"
#include "Tetris.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
	CTetris tetris;
	CGame &game = tetris.game;
	game.start();
		
	system("pause");
    return 0;
}

