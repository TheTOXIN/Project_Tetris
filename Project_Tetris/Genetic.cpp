#include "stdafx.h"
#include "Player.h"
#include "Game.h"
#include "Factory.h"
#include "Tetris.h"
#include "iostream"
#include "AI.h"
#include "Genetic.h"

using namespace std;

CGenetic::CGenetic(int width, int height) :
	GField(width, height),
	bestFigrue(width / 2 - 1, 0, 4, 0, CTetris::game.factory.space),
	GFigure(width / 2 - 1, 0, 4, 0, CTetris::game.factory.space)
{
	countEVO = 0;
	countDNA = 30;
	countGame = 5;
	countMove = 200;
	countBirth = countDNA / 3;
	generation();
}

void CGenetic::evolution()
{
	cout << "Genetic Algorithm start..." << endl;
	cout << "EVO." << countEVO + 1 << endl;

	fitness();
	sort();
	crossover();
	printPOP();

	cout << "Genetic Algorithm end..." << endl;
	bestCondidate = populations[0];
	printTheBestCondodate();
	countEVO++;
}

void CGenetic::fitness()
{
	for (int i = 0; i < countDNA; i++)
	{
		DNA &candidate = populations[i];
		candidate.fitness = 0;
		for (int j = 0; j < countGame; j++)
		{
			GField.clearField();
			bool isGameOver = false;
			int countLineScore = 0;
			GFigure = CTetris::game.factory.createFigure(0);
			int k = 0;
			while (!isGameOver && k < countMove)
			{
				searchMove(candidate);
				bestFigrue.land(GField);
				countLineScore += GField.remove();
				isGameOver = bestFigrue.getY() <= 0;
				GFigure = CTetris::game.factory.createFigure(GFigure.index);
				k++;
			}
		}
	}
}

void CGenetic::searchMove(DNA &candidate)
{
	double bestScore = -99999;
	double tmpScore = 0;

	for (int i = 0; i < 4; i++)
	{
		GFigure.x = 0;
		GFigure.y = 0;
		GFigure.countRotate(1);
		GFigure.moveToAngle(GField);

		while (GFigure.isMaxRight(GField))
		{
			GFigure.downMax(GField);
			CField landField = GField;
			GFigure.land(landField);

			int lines = landField.countLines();
			if (lines > 0) candidate.fitness += lines;
			landField.remove();

			tmpScore = (-candidate.heightWeight * landField.countHeight()) + (candidate.linesWeight * lines) +
				(-candidate.holesWeight * landField.countHoles()) + (-candidate.monotontWeight * landField.countMonoton());

			if (tmpScore > bestScore)
			{
				bestScore = tmpScore;
				bestFigrue = GFigure;
				bestFigrue.r = i + 1;
			}

			GFigure.upMax(GField);
			GFigure.x++;
		}
	}
}

void CGenetic::selection(DNA parents[2])
{
	parents[0] = populations[rand() % (countDNA / 3)];
	parents[1] = populations[rand() % (countDNA / 3)];

	for (int i = 0; i < 3; i++)
	{
		DNA parent1 = populations[rand() % (countDNA / 3)];
		DNA parent2 = populations[rand() % (countDNA / 3)];

		if (parent1.fitness > parents[0].fitness)
			parents[0] = parent1;
		if (parent2.fitness > parents[1].fitness)
			parents[1] = parent2;
	}
}

void CGenetic::mutation(DNA &candidate)
{
	int random = rand() % 10;
	int parametr = rand() % 4;
	double quantity = (double)(rand()) / RAND_MAX;
	if (random == 1)
	{
		switch (parametr)
		{
		case 0: candidate.heightWeight = quantity; break;
		case 1: candidate.linesWeight = quantity; break;
		case 2: candidate.holesWeight = quantity; break;
		case 3: candidate.monotontWeight = quantity; break;
		}
	}
}

void CGenetic::crossover()
{
	DNA parents[2];
	DNA birth;
	for (int i = 0; i < countBirth; i++)
	{
		selection(parents);

		birth.heightWeight = parents[0].fitness * parents[0].heightWeight + parents[1].fitness * parents[1].heightWeight;
		birth.linesWeight = parents[0].fitness * parents[0].linesWeight + parents[1].fitness * parents[1].linesWeight;
		birth.holesWeight = parents[0].fitness * parents[0].holesWeight + parents[1].fitness * parents[1].holesWeight;
		birth.monotontWeight = parents[0].fitness * parents[0].monotontWeight + parents[1].fitness * parents[1].monotontWeight;
		birth.fitness = 0;

		mutation(birth);
		normalize(birth);
		birth.number = populations[countDNA - 1 - i].number;
		populations[countDNA - 1 - i] = birth;
	}
}

void CGenetic::sort()
{
	for (int i = 0; i < countDNA - 1; i++)
	{
		for (int j = i + 1; j < countDNA; j++)
		{
			if (populations[i].fitness < populations[j].fitness)
			{
				DNA tmp = populations[i];
				populations[i] = populations[j];
				populations[j] = tmp;
			}
		}
	}
}

void CGenetic::normalize(DNA &candidate)
{
	double norm = sqrt(pow(candidate.heightWeight, 2) +
		pow(candidate.linesWeight, 2) +
		pow(candidate.holesWeight, 2) +
		pow(candidate.monotontWeight, 2));
	candidate.heightWeight /= norm;
	candidate.linesWeight /= norm;
	candidate.holesWeight /= norm;
	candidate.monotontWeight /= norm;
}

void CGenetic::generation()
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i < countDNA; i++)
	{
		populations[i].heightWeight = (double)(rand()) / RAND_MAX;
		populations[i].linesWeight = (double)(rand()) / RAND_MAX;
		populations[i].holesWeight = (double)(rand()) / RAND_MAX;
		populations[i].monotontWeight = (double)(rand()) / RAND_MAX;
		populations[i].fitness = 0;
		populations[i].number = i + 1;
		normalize(populations[i]);
	}
}

void CGenetic::printGAME(CField &GField, CFigure &GFigure, int score)
{
	CTetris::game.printer.print(GField, GFigure, bestFigrue, 0, score);
}

void CGenetic::printPOP()
{
	cout << "POPULATIONS" << endl;
	for (int i = 0; i < countDNA; i++)
	{
		cout << populations[i].number << ". | ";
		cout << populations[i].heightWeight << " | ";
		cout << populations[i].linesWeight << " | ";
		cout << populations[i].holesWeight << " | ";
		cout << populations[i].monotontWeight << " | ";
		cout << "F = " << populations[i].fitness << endl;
	}
	cout << endl;
}

void CGenetic::printINFO(CField &GField, DNA &candidate, double &tmpScore, double &bestScore)
{
	cout << "=========== INFO." << candidate.number << " ===========" << endl;
	cout << "Whight: ";
	cout << candidate.heightWeight << " | ";
	cout << candidate.linesWeight << " | ";
	cout << candidate.holesWeight << " | ";
	cout << candidate.monotontWeight << endl;
	cout << "Stage: ";
	cout << GField.countHeight() << " | ";
	cout << GField.countLines() << " | ";
	cout << GField.countHoles() << " | ";
	cout << GField.countMonoton() << endl;
	cout << "Score: " << tmpScore << endl;
	cout << "Fitness: " << candidate.fitness << endl;
	cout << "Best score: " << bestScore << endl;
	cout << "Best figrue x: " << bestFigrue.x << endl << endl;
}

void CGenetic::printBIRTH(DNA &birth, DNA parents[2])
{
	cout << "Birth:" << endl;
	cout << birth.number << ". | ";
	cout << birth.heightWeight << " | ";
	cout << birth.linesWeight << " | ";
	cout << birth.holesWeight << " | ";
	cout << birth.monotontWeight << " | ";
	cout << "F = " << birth.fitness << endl;

	cout << "Parent1:" << endl;
	cout << parents[0].number << ". | ";
	cout << parents[0].heightWeight << " | ";
	cout << parents[0].linesWeight << " | ";
	cout << parents[0].holesWeight << " | ";
	cout << parents[0].monotontWeight << " | ";
	cout << "F = " << parents[0].fitness << endl;

	cout << "Parent2:" << endl;
	cout << parents[1].number << ". | ";
	cout << parents[1].heightWeight << " | ";
	cout << parents[1].linesWeight << " | ";
	cout << parents[1].holesWeight << " | ";
	cout << parents[1].monotontWeight << " | ";
	cout << "F = " << parents[1].fitness << endl << endl;
}

void CGenetic::printTheBestCondodate()
{
	cout << "THE BEST | ";
	cout << bestCondidate.number << ". | ";
	cout << bestCondidate.heightWeight << " | ";
	cout << bestCondidate.linesWeight << " | ";
	cout << bestCondidate.holesWeight << " | ";
	cout << bestCondidate.monotontWeight << " | ";
	cout << "F = " << bestCondidate.fitness << endl;
}


