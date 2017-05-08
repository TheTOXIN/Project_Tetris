#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Factory.h"
#include "Tetris.h"
#include "Field.h"
#include "AI.h"
#include "conio.h"

CPlayer::CPlayer(int width, int height) :
	figure(width / 2 - 1, 0, 4, 0, CTetris::game.factory.space),
	nextFigure(width / 2 - 1, 0, 4, 0, CTetris::game.factory.space),
	field(width, height)
{
	isGameOver = false;
}

void CPlayer::initialize()
{
	figure = CTetris::game.factory.createFigure();
	nextFigure = CTetris::game.factory.createFigure();
	field.clearField();
	score = 0;
	isGameOver = false;
}

void CPlayer::step()
{
	if (!isGameOver)
	{
		figure.down();
		if (!figure.isCurrentPos(field))
		{
			figure.up();
			figure.land(field);
			isGameOver = figure.getY() <= 0;
			if (field.countLines() != 0)
			{
				CMediaPlayer::playSoundRemove();
				score += field.remove();
			}
			if (!isGameOver)
			{
				figure = nextFigure;
				nextFigure = CTetris::game.factory.createFigure();
			}
		}
	}
}

void CPlayer::controller()
{
	if (!isGameOver)
	{
		switch (_getch())
		{
		case 72: figure.rotate(field); break;//ROTATE
		case 80: figure.downMax(field); break;//DOWN
		case 75: figure.left(field); break;//LEFT
		case 77: figure.right(field); break;//RIGHT
		}
	}
}
