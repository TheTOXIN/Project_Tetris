#pragma once

class CMediaPlayer
{
public:
	static void loader();
	static void playMusicMenu();
	static void playMusicGame();
	static void stopMusicMenu();
	static void stopMusicGame();
	static void playSoundTick();
	static void playSoundLand();
	static void playSoundRemove();
	static void playSoundMove();
	static void playSoundRotate();
	static void mute(bool b);
private:
};
