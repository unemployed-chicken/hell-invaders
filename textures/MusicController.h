#pragma once
#include "DoubleLinkedList.h"
#include "GamingMusic.h"
#include "Properties.h"
#include <map>
using std::map;
using std::string;
using std::make_shared;

const string game_play_songs[6]{
	"audio/metal-headed.mp3", "audio/fierce.mp3", "audio/doom-extreme-metal-rock.mp3",
	"audio/metal-header.mp3", "audio/rise-of-the-zombies.mp3", "audio/we-can-win.mp3"
};

class MusicController {
	shared_ptr<Node<GamingMusic>> Current_music = nullptr;
	shared_ptr<Node<GamingMusic>> Main_screen_music = nullptr;
	DoubleLinkedList<GamingMusic> Mid_game_music_list;
	float Master_volume; // Controlled by props, must be reloaded when Props is updated
	bool Is_music_on;

	

	// confirmed private
	void rotateMusic(bool is_game_play);
	void updateAllMusicVolume();
	void generateMidGameMusicList();
	void generateMusic();


public:
	MusicController(float volume, bool is_music_on);

	shared_ptr<Node<GamingMusic>> getCurrentMusic();
	void setCurrentMusicToGameplayMusic();
	void playCurrentMusic(bool is_game_play);
	void reloadPropertyImpactedValues(Properties& properties);
	void restartCurrentMusic();
	void cleanUpMusic();
	void setIsMusicOn(const bool is_music_on);
};

