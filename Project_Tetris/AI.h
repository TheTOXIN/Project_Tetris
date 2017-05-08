#pragma once

#include "Field.h"
#include "Figure.h"
#include "Genetic.h"

class CComputer
{
public:
	CComputer(int width, int height);
	void initialize();
	CField AIField;
	CFigure AIFigure;
	CFigure AINextFigure;
	CFigure AIBestFigure;
	CGenetic AIGenetic;
	bool AIisGameOver;
	int AIscore;
	void AIstep();
	void AIController();
	void AISatrtEvolution();
	void AISearchMove();
private:
};

