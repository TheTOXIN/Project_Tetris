#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Player.h"
#include "AI.h"
#include "Tetris.h"
#include "WindowView.h"
#include "KeyController.h"
#include "MediaPlayer.h"

using namespace sf;

void CKeyController::keyMenu(RenderWindow & window, CWindowView & wv)
{
	if (checkClick(wv.play_S, window, wv, wv.play_S.getGlobalBounds()))
	{
		CMediaPlayer::playSoundTick();
		CTetris::game.windowMode = 2;
		CTetris::game.listMode = 1;
	}

	if (checkClick(wv.btn_info_S, window, wv, wv.btn_info_S.getGlobalBounds()))
	{
		CMediaPlayer::playSoundTick();
		CTetris::game.windowMode = 2;
		CTetris::game.listMode = 2;
	}

	if (checkClick(wv.btn_settings_S, window, wv, wv.btn_settings_S.getGlobalBounds()))
	{
		CMediaPlayer::playSoundTick();
		CTetris::game.windowMode = 2;
		CTetris::game.listMode = 3;
	}
}

void CKeyController::keyList(RenderWindow & window, CWindowView & wv)
{
	if (checkClick(wv.exit_S, window, wv, wv.exit_S.getGlobalBounds()))
	{
		CMediaPlayer::playSoundTick();
		CTetris::game.windowMode = 1;
		CTetris::game.listMode = 0;
		CTetris::game.gameMode = 0;
	}

	switch (CTetris::game.listMode)
	{
	case 1:
	{
		if (checkClick(wv.player1_S, window, wv, wv.player1_S.getGlobalBounds()))
		{
			CMediaPlayer::playSoundTick();
			CTetris::game.windowMode = 3;
			CTetris::game.listMode = 0;
			CTetris::game.gameMode = 1;
		}

		if (checkClick(wv.player2_S, window, wv, wv.player2_S.getGlobalBounds()))
		{
			CMediaPlayer::playSoundTick();
			CTetris::game.windowMode = 3;
			CTetris::game.listMode = 0;
			CTetris::game.gameMode = 2;
		}

		if (checkClick(wv.aiplayer_S, window, wv, wv.aiplayer_S.getGlobalBounds()))
		{
			CMediaPlayer::playSoundTick();
			CTetris::game.windowMode = 3;
			CTetris::game.listMode = 0;
			CTetris::game.gameMode = 3;
		}

		if (checkClick(wv.training_S, window, wv, wv.training_S.getGlobalBounds()))
		{
			CMediaPlayer::playSoundTick();
			CTetris::game.windowMode = 3;
			CTetris::game.listMode = 0;
			CTetris::game.gameMode = 4;
		}
	}
	break;
	case 2:
	{
		if (checkClick(wv.gitlink_S, window, wv, wv.gitlink_S.getGlobalBounds()))
		{
			CMediaPlayer::playSoundTick();
			ShellExecute(NULL, L"open", L"https://github.com/TheTOXIN/Project_Tetris.git", NULL, NULL, SW_SHOW);
		}

		if (checkClick(wv.control_S, window, wv, wv.control_S.getGlobalBounds()))
		{
			CMediaPlayer::playSoundMove();
		}
	}
	break;
	case 3:
	{
		FloatRect setUp(wv.settemp_S.getPosition().x + 250, wv.settemp_S.getPosition().y, 100, 40);
		FloatRect setDown(wv.settemp_S.getPosition().x + 250, wv.settemp_S.getPosition().y + 40, 100, 40);
		FloatRect setON(wv.setmusic_S.getPosition().x + 250, wv.setmusic_S.getPosition().y, 100, 40);
		FloatRect setOFF(wv.setmusic_S.getPosition().x + 250, wv.setmusic_S.getPosition().y + 40, 100, 40);
	
		if (checkClick(wv.settemp_S, window, wv, setUp))
		{
			CMediaPlayer::playSoundTick();
			CTetris::game.setTEMP += 0.01;
		}


		if (checkClick(wv.settemp_S, window, wv, setDown))
		{
			CMediaPlayer::playSoundTick();
			CTetris::game.setTEMP -= 0.01;
		}
		
		if (checkClick(wv.setmusic_S, window, wv, setON))
		{
			CMediaPlayer::playSoundTick();
			CMediaPlayer::mute(false);
		}

		if (checkClick(wv.setmusic_S, window, wv, setOFF))
		{
			CMediaPlayer::playSoundTick();
			CMediaPlayer::mute(true);
		}

		wv.settemp_S.setColor(Color::White);
		wv.setmusic_S.setColor(Color::White);
	}
	break;
	}
}

void CKeyController::keyGame(RenderWindow & window, CWindowView & wv)
{
	if (checkClick(wv.exit_S, window, wv, wv.exit_S.getGlobalBounds()))
	{
		exit();
	}

	if (checkClick(wv.pause_S, window, wv, wv.pause_S.getGlobalBounds()))
	{
		CMediaPlayer::playSoundTick();
		wv.pause_S.setColor(Color(81, 81, 81));
		CTetris::game.isPause = !CTetris::game.isPause;
	}
}

bool CKeyController::checkClick(Sprite & sprite, RenderWindow & window, CWindowView & wv, FloatRect rect)
{
	Event event;
	Vector2i posMouse = Mouse::getPosition(window);
	sprite.setColor(Color::White);
	if (rect.contains(posMouse.x, posMouse.y))
	{
		sprite.setColor(Color(81, 81, 81));
		while (window.pollEvent(event))
			if (event.type == sf::Event::MouseButtonPressed)
				if (event.key.code == sf::Mouse::Left)
					return true;
	}
	return false;
}

void CKeyController::playerControl(RenderWindow & window, CPlayer & player1, CPlayer & player2)
{	
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			if (!player1.isGameOver)
			{
				if (Keyboard::isKeyPressed(Keyboard::W)) {
					player1.figure.rotate(player1.field);
					CMediaPlayer::playSoundRotate();
				}
				if (Keyboard::isKeyPressed(Keyboard::S)) {
					player1.figure.downMax(player1.field);
					CMediaPlayer::playSoundLand();
				}
				if (Keyboard::isKeyPressed(Keyboard::D)) {
					player1.figure.right(player1.field);
					CMediaPlayer::playSoundMove();
				}
				if (Keyboard::isKeyPressed(Keyboard::A)) {
					player1.figure.left(player1.field);
					CMediaPlayer::playSoundMove();
				}
			}

			if (!player2.isGameOver)
			{
				if (Keyboard::isKeyPressed(Keyboard::Up)) {
					player2.figure.rotate(player2.field);
					CMediaPlayer::playSoundRotate();
				}
				if (Keyboard::isKeyPressed(Keyboard::Down)) {
					player2.figure.downMax(player2.field);
					CMediaPlayer::playSoundLand();
				}
				if (Keyboard::isKeyPressed(Keyboard::Right)) {
					player2.figure.right(player2.field);
					CMediaPlayer::playSoundMove();
				}
				if (Keyboard::isKeyPressed(Keyboard::Left)) {
					player2.figure.left(player2.field);
					CMediaPlayer::playSoundMove();
				}
			}
		}
	}
}

void CKeyController::exit()
{
	CMediaPlayer::playSoundTick();
	CMediaPlayer::stopMusicGame();
	CMediaPlayer::playMusicMenu();
	CTetris::game.windowMode = 2;
	CTetris::game.listMode = 1;
	CTetris::game.gameMode = 0;
}
