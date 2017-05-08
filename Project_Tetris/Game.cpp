#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "Game.h"
#include "Factory.h"
#include "Tetris.h"
#include "AI.h"
#include "WindowView.h"
#include "MediaPlayer.h"
#include <iostream> 
#include <string> 

using namespace sf;

CGame::CGame(int width, int height) : 
	player1(width, height), player2(width, height), computer(width, height), window(VideoMode(800,480), "Projet_Tetris")
{
	wv.icon.loadFromFile("res/image/icon.png");
	window.setIcon(32, 32, wv.icon.getPixelsPtr());
	wv.loading.loadFromFile("res/image/loading.png");
	wv.loading_S.setTexture(wv.loading);
	wv.showLoading(window);
	wv.loader();
	wv.width = 800;
	wv.height = 480;
	window.setFramerateLimit(60);
	windowMode = 1;
	listMode = 0;
	gameMode = 0;
	setTEMP = 0.5;
	temp = 0.5;
	CMediaPlayer::loader();
	CMediaPlayer::playMusicMenu();
}

void CGame::start()
{
	while (true)
	{
		switch (windowMode)
		{
		case 1: menuUpdate(); break;
		case 2: listUpdate(); break;
		case 3: gameUpdate(); break;
		}
	}
}

void CGame::menuUpdate()
{
	wv.setBackground(wv.background_3_S);
	while (windowMode == 1)
	{
		tickTack();
		wv.showMenu(window);
		kc.keyMenu(window, wv);
	}
}

void CGame::listUpdate()
{
	wv.setBackground(wv.background_1_S);
	while (windowMode == 2)
	{
		tickTack();
		wv.showList(window);
		kc.keyList(window, wv);
	}
}

void CGame::gameUpdate()
{
	CMediaPlayer::stopMusicMenu();
	CMediaPlayer::playMusicGame();
	wv.setBackground(wv.background_2_S);
	isPause = false;

	if (gameMode == 1)
	{
		player1.initialize();
		while (gameMode == 1)
		{
			tickTack();	
			if (!player1.isGameOver && !isPause)
			{
				if (wv.tick > temp)
				{
					player1.step();
					updateTmp(player1.score);
					CMediaPlayer::playSoundTick();
					wv.tick = 0;
				}
				kc.playerControl(window, player1, player1);
			}
			wv.showGame(window, player1, player2, computer);
			kc.keyGame(window, wv);
		}
	}
	
	if (gameMode == 2)
	{
		player1.initialize();
		player2.initialize();
		while (gameMode == 2)
		{
			tickTack();
			if ((!player1.isGameOver || !player2.isGameOver) && !isPause)
			{
				if (wv.tick > temp)
				{
					player1.step();
					player2.step();
					updateTmp((player1.score + player2.score) / 2);
					CMediaPlayer::playSoundTick();
					wv.tick = 0;
				}
				kc.playerControl(window, player1, player2);
			}
			wv.showGame(window, player1, player2, computer);
			kc.keyGame(window, wv);
		}
	}

	if (gameMode == 3)
	{
		player1.initialize();
		computer.initialize();
		while (gameMode == 3)
		{
			tickTack();
			if ((!player1.isGameOver || !computer.AIisGameOver) && !isPause)
			{
				if (wv.tick > temp)
				{
					player1.step();
					updateTmp((player1.score + computer.AIscore) / 2);
					computer.AIstep();
					CMediaPlayer::playSoundTick();
					wv.tick = 0;
				}
				kc.playerControl(window, player1, player1);
			}
			wv.showGame(window, player1, player2, computer);
			kc.keyGame(window, wv);
		}
	}

	if (gameMode == 4)
	{
		temp = setTEMP / 5;
		wv.showLoading(window);
		computer.AISatrtEvolution();
		wv.showEvolution(window, computer);
		computer.initialize();
		clock.restart();

		while (gameMode == 4)
		{
			tickTack();
			if (!computer.AIisGameOver && !isPause)
			{
				if (wv.tick > temp)
				{
					computer.AIstep();
					CMediaPlayer::playSoundTick();
					wv.tick = 0;
				}
			}
			wv.showGame(window, player1, player2, computer);
			kc.keyGame(window, wv);
		}
		temp = setTEMP;
	}
}

void CGame::tickTack()
{
	wv.timer = clock.getElapsedTime().asMicroseconds();
	wv.tick += clock.getElapsedTime().asSeconds();
	wv.timer /= 800;
	clock.restart();
}

void CGame::updateTmp(int score)
{
	temp = setTEMP;
	int n = score / 1000;
	for (int i = 0; i < n; i++)
		temp -= 0.025;
}
