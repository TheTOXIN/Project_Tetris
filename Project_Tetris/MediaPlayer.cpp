#include "stdafx.h"
#include "Player.h"
#include "WindowView.h"
#include "MediaPlayer.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Main.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

SoundBuffer bufferTick;
Sound tick;
SoundBuffer bufferRotate1;
Sound rotate1;
SoundBuffer bufferRotate2;
Sound rotate2;
SoundBuffer bufferMove1;
Sound move1;
SoundBuffer bufferMove2;
Sound move2;
SoundBuffer bufferClear;
Sound clear;
SoundBuffer bufferLand;
Sound land;

Music main;
Music game;

void CMediaPlayer::loader()
{
	bufferTick.loadFromFile("res/sound/tick.wav");
	tick.setBuffer(bufferTick);
	
	bufferRotate1.loadFromFile("res/sound/rotate_1.wav");
	rotate1.setBuffer(bufferRotate1);

	bufferRotate2.loadFromFile("res/sound/rotate_2.wav");
	rotate2.setBuffer(bufferRotate2);

	bufferMove1.loadFromFile("res/sound/move_1.wav");
	move1.setBuffer(bufferMove1);

	bufferMove2.loadFromFile("res/sound/move_2.wav");
	move2.setBuffer(bufferMove2);

	bufferClear.loadFromFile("res/sound/remove.wav");
	clear.setBuffer(bufferClear);
	clear.setVolume(50);

	bufferLand.loadFromFile("res/sound/land.wav");
	land.setBuffer(bufferLand);

	main.openFromFile("res/music/ShootingStars.ogg");
	main.setLoop(true);
	main.setVolume(10);

	game.openFromFile("res/music/TetrisTheme.ogg");
	game.setLoop(true);
	game.setVolume(50);
}

void CMediaPlayer::playMusicMenu()
{
	main.play();
}

void CMediaPlayer::playMusicGame()
{
	game.play();
}

void CMediaPlayer::stopMusicMenu()
{
	main.stop();
}

void CMediaPlayer::stopMusicGame()
{
	game.stop();
}

void CMediaPlayer::playSoundTick()
{
	tick.play();
}

void CMediaPlayer::playSoundLand()
{
	land.play();
}

void CMediaPlayer::playSoundRemove()
{
	clear.play();
}

void CMediaPlayer::playSoundMove()
{
	if (rand() % 2)
		move1.play();
	else
		move2.play();
}

void CMediaPlayer::playSoundRotate()
{
	if (rand() % 2)
		rotate1.play();
	else
		rotate2.play();
}

void CMediaPlayer::mute(bool b)
{
	if (b)
	{
		main.setVolume(0);
		game.setVolume(0);
	}
	else
	{
		main.setVolume(10);
		game.setVolume(50);
	}
}
