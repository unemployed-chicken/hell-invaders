#pragma once
#include "raylib.h"
#include <memory>
#include <iostream>
using std::shared_ptr;
using std::string;

class GameMusic {
	Music Song;
	string Name;
	float Time_played{ 0.0f };
	bool Is_off{ false };

public:
	GameMusic(Music song, string name);
	GameMusic();
	void playMusic();
	void stopMusic();

	float getTimePlayed();
};

