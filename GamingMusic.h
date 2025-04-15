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
	//string Name; // TODO: Do I need name?
	float Time_played{ 0.0f };
	bool Is_on{ true };
	float Volume;

public:
	//GamingMusic(Music song, string name); // TODO: Do I need name?
	GamingMusic(Music song, float volume);
	GamingMusic();
	void stopMusic();
	void reloadMusicVolume();
	void setVolume(float volume);
	void cleanUpSong();

	float getTimePlayed();
	bool playMusic();
	bool getIsOn();
	Music getSong();
};

