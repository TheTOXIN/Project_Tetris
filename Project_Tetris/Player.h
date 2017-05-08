#pragma once

#include "Field.h"
#include "Figure.h"

class CPlayer
{
public:
	CPlayer(int width, int height);
	void initialize();
	CField field;
	CFigure figure;
	CFigure nextFigure;
	bool isGameOver;
	int score;
	void step();
	void controller();
private:
};