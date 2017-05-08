#include "stdafx.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "iostream"
#include "Tetris.h"
#include "AI.h"
#include "Player.h"
#include "WindowView.h"
#include "MediaPlayer.h"

using namespace sf;
using namespace std;

void CWindowView::showEvolution(RenderWindow & window, CComputer & computer)
{
	Text complete("", font, 50);
	Text press("", font, 50);
	Text info("", font, 25);
	
	press.setString("PRESS 'Space'");
	complete.setString("EVOLUTION COMPLETE");
	info.setString("EVO: " + std::to_string(computer.AIGenetic.countEVO) + '\n' +
		"Index: " + std::to_string(computer.AIGenetic.bestCondidate.number) + '\n' +
		"Heights: " + std::to_string(computer.AIGenetic.bestCondidate.heightWeight) + '\n' +
		"Lines: " + std::to_string(computer.AIGenetic.bestCondidate.linesWeight) + '\n' +
		"Holes: " + std::to_string(computer.AIGenetic.bestCondidate.holesWeight) + '\n' +
		"Monoton: " + std::to_string(computer.AIGenetic.bestCondidate.monotontWeight) + '\n' +
		"Fitness: " + std::to_string(computer.AIGenetic.bestCondidate.fitness) + '\n');

	press.setPosition(180, 400);
	complete.setPosition(80, 10);
	info.setPosition(270, 120);

	window.clear(Color(0, 0, 0));
	window.draw(complete);
	window.draw(info);
	window.draw(press);
	window.display();

	while (true)
	{
		checkCloseWindow(window);
		if (Keyboard::isKeyPressed(Keyboard::Space))
			break;
	}
}

void CWindowView::showLoading(RenderWindow & window)
{
	loading_S.setPosition(0, 0);
	window.clear();
	window.draw(loading_S);
	window.display();
}

void CWindowView::showMenu(RenderWindow & window)
{
	window.clear();

	checkCloseWindow(window);
	moveBackground(background_3_S);

	field_S.setPosition(width / 2 - field.getSize().x / 2, 0);
	logo_S.setPosition(width / 2 - logo.getSize().x / 2, 10);
	play_S.setPosition(width / 2 - play.getSize().x / 2, 220);
	btn_settings_S.setPosition(play_S.getPosition().x, play_S.getPosition().y + 100);
	btn_info_S.setPosition(play_S.getPosition().x + play.getSize().x - btn_info.getSize().x, btn_settings_S.getPosition().y);

	window.draw(background_3_S);
	window.draw(tmpBack);
	window.draw(field_S);
	window.draw(logo_S);
	window.draw(play_S);
	window.draw(btn_settings_S);
	window.draw(btn_info_S);
	window.display();
}

void CWindowView::showList(RenderWindow & window)
{
	Text text("", font, 50);
	Text temp_T("", font, 25);

	checkCloseWindow(window);
	moveBackground(background_1_S);

	list_S.setPosition(width / 2 - list.getSize().x / 2, 0);
	exit_S.setPosition(width / 2 - exit.getSize().x / 2, list.getSize().y);

	window.clear();
	window.draw(background_1_S);
	window.draw(tmpBack);
	window.draw(list_S);
	window.draw(exit_S);

	switch (CTetris::game.listMode)
	{
	case 1:
	{
		text.setString("GAMEODE");
		text.setPosition(width / 2 - 135, 1);
		player1_S.setPosition(width / 2 - player1.getSize().x / 2, 90);
		player2_S.setPosition(width / 2 - player2.getSize().x / 2, 160);
		aiplayer_S.setPosition(width / 2 - aiplayer.getSize().x / 2, 230);
		training_S.setPosition(width / 2 - training.getSize().x / 2, 300);

		window.draw(player1_S);
		window.draw(player2_S);
		window.draw(training_S);
		window.draw(aiplayer_S);
	}
	break;
	case 2:
	{
		text.setString("INFO");
		text.setPosition(width / 2 - 55, 1);
		gitlink_S.setPosition(width / 2 - gitlink.getSize().x / 2, 90);
		control_S.setPosition(width / 2 - control.getSize().x / 2, 180);

		window.draw(gitlink_S);
		window.draw(control_S);
	}
	break;
	case 3:
	{
		text.setString("SETTINGS");
		text.setPosition(width / 2 - 135, 1);
		temp_T.setString(to_string(CTetris::game.setTEMP).substr(0, 5));
		temp_T.setPosition(settemp_S.getPosition().x + 150, settemp_S.getPosition().y + 23);
		settemp_S.setPosition(width / 2 - settemp.getSize().x / 2, 120);
		setmusic_S.setPosition(width / 2 - setmusic.getSize().x / 2, 230);

		window.draw(settemp_S);
		window.draw(setmusic_S);
		window.draw(temp_T);
	}
	break;
	}

	window.draw(text);
	window.display();
}

void CWindowView::showGame(RenderWindow & window, CPlayer &playe1, CPlayer &player2, CComputer &computer)
{
	Text score1("", font, 50);
	Text score2("", font, 50);
	Text temp_T("", font, 24);
	Text text("", font, 20);

	checkCloseWindow(window);
	moveBackground(background_2_S);

	exit_S.setPosition(width - exit.getSize().x - 5, 5);
	pause_S.setPosition(5, 5);
	temp_T.setPosition(temp_S.getPosition().x + 9, temp_S.getPosition().y + 60);
	temp_T.setString(to_string(CTetris::game.temp).substr(0, 5));

	window.clear();
	window.draw(tmpBack);
	window.draw(background_2_S);
	window.draw(exit_S);
	window.draw(pause_S);

	if (CTetris::game.gameMode == 1 || CTetris::game.gameMode == 4)
	{
		field_S.setPosition(width / 2 - field.getSize().x /2, 0);
		next_S.setPosition(field_S.getPosition().x + field.getSize().x - 10, 0);
		temp_S.setPosition(field_S.getPosition().x + 10 - 100, height - 100);
		grid_S.setPosition(width / 2 - field.getSize().x / 2, 5);
		score1.setPosition(field_S.getPosition().x + 10, field_S.getPosition().y + 10);

		window.draw(field_S);
		window.draw(next_S);
		window.draw(temp_S);
		window.draw(grid_S);

		if (CTetris::game.gameMode == 1)
		{
			printField(window, playe1.field, playe1.figure, 296, 99);
			printFigrue(window, playe1.nextFigure, next_S.getPosition().x + 10, next_S.getPosition().y + 60);
			score1.setString(std::to_string(playe1.score));
			window.draw(score1);
		}

		if (CTetris::game.gameMode == 4)
		{
			printField(window, computer.AIField, computer.AIFigure, 296, 99);
			printFigrue(window, computer.AINextFigure, next_S.getPosition().x + 10, next_S.getPosition().y + 60);
			score1.setString(std::to_string(computer.AIscore));
			text.setString("EVO " + std::to_string(computer.AIGenetic.countEVO));
			text.setPosition(score1.getPosition().x + 75, score1.getPosition().y + 50);
			window.draw(score1);
			window.draw(text);
		}
	}

	if (CTetris::game.gameMode == 2 || CTetris::game.gameMode == 3)
	{
		next_S.setPosition(5, height - next.getSize().y - 5);
		field_S.setPosition(next.getSize().x + next_S.getPosition().x + 5, 0);
		grid_S.setPosition(next.getSize().x + next_S.getPosition().x + 5, 5);
		score1.setPosition(field_S.getPosition().x + 10, field_S.getPosition().y + 10);
		temp_S.setPosition(field_S.getPosition().x + field.getSize().x + 10, field_S.getPosition().y + 10);
		field_S_2.setPosition(temp_S.getPosition().x + temp.getSize().x + 10, 0);
		grid_S_2.setPosition(temp_S.getPosition().x + temp.getSize().x + 10, 5);
		next_S_2.setPosition(width - next.getSize().x - 5, height - next.getSize().y - 5);
		score2.setPosition(field_S_2.getPosition().x + 10, field_S_2.getPosition().y + 10);

		window.draw(field_S);
		window.draw(next_S);
		window.draw(grid_S);
		window.draw(field_S_2);
		window.draw(next_S_2);
		window.draw(grid_S_2);

		if (CTetris::game.gameMode == 2)
		{
			printField(window, playe1.field, playe1.figure, 120, 99);
			printFigrue(window, playe1.nextFigure, next_S.getPosition().x + 10, next_S.getPosition().y + 60);
			score1.setString(std::to_string(playe1.score));
			window.draw(score1);

			printField(window, player2.field, player2.figure, 470, 99);
			printFigrue(window, player2.nextFigure, next_S_2.getPosition().x + 10, next_S_2.getPosition().y + 60);
			score2.setString(std::to_string(player2.score));
			window.draw(score2);
		}
		if (CTetris::game.gameMode == 3)
		{
			printField(window, playe1.field, playe1.figure, 120, 99);
			printFigrue(window, playe1.nextFigure, next_S.getPosition().x + 10, next_S.getPosition().y + 60);
			score1.setString(std::to_string(playe1.score));
			window.draw(score1);

			printField(window, computer.AIField, computer.AIFigure, 470, 99);
			printFigrue(window, computer.AINextFigure, next_S_2.getPosition().x + 10, next_S_2.getPosition().y + 60);
			score2.setString(std::to_string(computer.AIscore));
			text.setString("EVO " + std::to_string(computer.AIGenetic.countEVO));
			text.setPosition(score2.getPosition().x + 75, score2.getPosition().y + 50);
			window.draw(score2);
			window.draw(text);
		}
	}

	window.draw(temp_S);
	window.draw(temp_T);
	window.display();
}

void CWindowView::printField(RenderWindow &window, CField & field, CFigure & figure, int x, int y)
{
	int canvas[20][10];

	for (int i = 0; i < field.getHeight(); i++)
	{
		for (int j = 0; j < field.getWidth(); j++)
		{
			canvas[i][j] = field.matrix[i][j];
		}
	}

	int left = figure.getX();
	int top = figure.getY();

	for (int i = 0; i < figure.size; i++)
	{
		for (int j = 0; j < figure.size; j++)
		{
			if (top + i >= field.getHeight() || left + j >= field.getWidth()) continue;
			if (figure.matrix[i][j] == 1)
			{
				canvas[top + i][left + j] = figure.index;
			}
		}
	}

	for (int i = 0; i < field.getHeight(); i++)
	{
		for (int j = 0; j < field.getWidth(); j++)
		{
			if (canvas[i][j] != 0)
			{
				bricks_S.setTextureRect(IntRect(20 * canvas[i][j], 0, 20, 20));
				bricks_S.setPosition(j * 20 + x + j, i * (20-1) + y);
				window.draw(bricks_S);
			}
		}
	}
}

void CWindowView::printFigrue(RenderWindow &window, CFigure & figure, int x, int y)
{
	for (int i = 0; i < figure.size; i++)
	{
		for (int j = 0; j < figure.size; j++)
		{
			if (figure.matrix[i][j] != 0)
			{
				bricks_S.setTextureRect(IntRect(20 * figure.index, 0, 20, 20));
				bricks_S.setPosition(j * 20 + x + j, i * (20 - 1) + y);
				window.draw(bricks_S);
			}
		}
	}
}

void CWindowView::setBackground(Sprite & back)
{
	tmpBack = back;
	back.setPosition(0, 0);
	tmpBack.setPosition(0, -959);
}

void CWindowView::moveBackground(Sprite & back)
{
	tmpBack.setPosition(0, tmpBack.getPosition().y + 0.1*timer);
	back.setPosition(0, back.getPosition().y + 0.1*timer);
	if (tmpBack.getPosition().y >= 0)
	{
		back = tmpBack;
		tmpBack.setPosition(0, -959);
	}
}

void CWindowView::checkCloseWindow(RenderWindow & window)
{
	Event event;
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed)
			window.close();
}

void CWindowView::loader()
{
	aiplayer.loadFromFile("res/image/aiplayer.png");
	aiplayer_S.setTexture(aiplayer);
	background_1.loadFromFile("res/image/background_1.png");
	background_1_S.setTexture(background_1);
	background_2.loadFromFile("res/image/background_2.png");
	background_2_S.setTexture(background_2);
	background_3.loadFromFile("res/image/background_3.png");
	background_3_S.setTexture(background_3);
	bricks.loadFromFile("res/image/bricks.png");
	bricks_S.setTexture(bricks);
	btn_info.loadFromFile("res/image/btn_info.png");
	btn_info_S.setTexture(btn_info);
	btn_settings.loadFromFile("res/image/btn_settings.png");
	btn_settings_S.setTexture(btn_settings);
	exit.loadFromFile("res/image/exit.png");
	exit_S.setTexture(exit);
	field.loadFromFile("res/image/field.png");
	field_S.setTexture(field);
	grid.loadFromFile("res/image/grid.png");
	grid_S.setTexture(grid);
	list.loadFromFile("res/image/list.png");
	list_S.setTexture(list);
	logo.loadFromFile("res/image/logo.png");
	logo_S.setTexture(logo);
	next.loadFromFile("res/image/next.png");
	next_S.setTexture(next);
	pause.loadFromFile("res/image/pause.png");
	pause_S.setTexture(pause);
	play.loadFromFile("res/image/play.png");
	play_S.setTexture(play);
	player1.loadFromFile("res/image/player1.png");
	player1_S.setTexture(player1);
	player2.loadFromFile("res/image/player2.png");
	player2_S.setTexture(player2);
	temp.loadFromFile("res/image/temp.png");
	temp_S.setTexture(temp);
	training.loadFromFile("res/image/training.png");
	training_S.setTexture(training);
	settemp.loadFromFile("res/image/settemp.png");
	settemp_S.setTexture(settemp);
	setmusic.loadFromFile("res/image/setmusic.png");
	setmusic_S.setTexture(setmusic);
	gitlink.loadFromFile("res/image/gitlink.png");
	gitlink_S.setTexture(gitlink);
	control.loadFromFile("res/image/control.png");
	control_S.setTexture(control);
	font.loadFromFile("res/font/micronica.otf");
	grid_S_2 = grid_S;
	field_S_2 = field_S;
	next_S_2 = next_S;
}
