#pragma once

#include "WindowView.h"
#include "MediaPlayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "AI.h"
#include "Player.h"

using namespace sf;

class CWindowView
{
public:
	int width;
	int height;
	float timer;
	float tick;
	void showEvolution(RenderWindow &window, CComputer &computer);
	void showLoading(RenderWindow &window);
	void showMenu(RenderWindow &window);
	void showList(RenderWindow &window);
	void showGame(RenderWindow &window, CPlayer &player1, CPlayer &player2, CComputer &computer);
	void printField(RenderWindow &window, CField &field, CFigure &figure, int x, int y);
	void printFigrue(RenderWindow &window, CFigure &figure, int x, int y);
	void setBackground(Sprite &back);
	void moveBackground(Sprite &back);
	void checkCloseWindow(RenderWindow &window);
	void loader();
	Font font;
	Sprite tmpBack;
	Texture aiplayer;
	Sprite aiplayer_S;
	Texture background_1;
	Sprite background_1_S;
	Texture background_2;
	Sprite background_2_S;
	Texture background_3;
	Sprite background_3_S;
	Texture bricks;
	Sprite bricks_S;
	Texture btn_info;
	Sprite btn_info_S;
	Texture btn_settings;
	Sprite btn_settings_S;
	Texture exit;
	Sprite exit_S;
	Texture field;
	Sprite field_S;
	Sprite field_S_2;
	Texture grid;
	Sprite grid_S;
	Sprite grid_S_2;
	Texture list;
	Sprite list_S;
	Texture logo;
	Sprite logo_S;
	Texture next;
	Sprite next_S;
	Sprite next_S_2;
	Texture pause;
	Sprite pause_S;
	Texture play;
	Sprite play_S;
	Texture player1;
	Sprite player1_S;
	Texture player2;
	Sprite player2_S;
	Texture temp;
	Sprite temp_S;
	Texture training;
	Sprite training_S;
	Texture loading;
	Sprite loading_S;
	Texture settemp;
	Sprite settemp_S;
	Texture setmusic;
	Sprite setmusic_S;
	Texture gitlink;
	Sprite gitlink_S;
	Texture control;
	Sprite control_S;
	Image icon;
private:
};
