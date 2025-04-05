#pragma once
#include "raylib.h"
#include <memory>
#include <iostream>
using std::shared_ptr;
using std::string;

extern const bool debugging;

class GamingMusic
{
	Music Song;
	string Name;
	float Time_played{ 0.0f };
	bool Is_on{ true };

public:
	GamingMusic(Music song, string name);
	GamingMusic();
	void stopMusic();

	float getTimePlayed();
	bool playMusic();
	bool getIsOn();
	Music getSong();
};

