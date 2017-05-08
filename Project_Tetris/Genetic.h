#pragma once

#include "Field.h"
#include "Figure.h"

class CGenetic
{
private:
	struct DNA
	{
		double heightWeight;
		double linesWeight;
		double holesWeight;
		double monotontWeight;
		int fitness;
		int number;
	};
public:
	CGenetic(int width, int height);
	CFigure GFigure;
	CField GField;
	CFigure bestFigrue;
	DNA populations[500];
	DNA bestCondidate;
	void evolution();
	void fitness();
	void selection(DNA parents[2]);
	void mutation(DNA &candidate);
	void crossover();
	void generation();
	void sort();
	void normalize(DNA &candidate);
	void searchMove(DNA &candidate);
	int countEVO;
	int countDNA;
	int countMove;
	int countGame;
	int countBirth;
	void printGAME(CField &GField, CFigure &GFigure, int score);
	void printPOP();
	void printINFO(CField &GField, DNA &candidate, double &tmpScore, double &bestScore);
	void printBIRTH(DNA &birth, DNA parents[2]);
	void printTheBestCondodate();
};