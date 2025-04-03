#include "GameMusic.h"

GameMusic::GameMusic(Music song, string name) : Song(song), Name(name) {
}

GameMusic::GameMusic() {}

void GameMusic::playMusic() {
	UpdateMusicStream(Song);
	Time_played = GetMusicTimePlayed(Song) / GetMusicTimeLength(Song);
	if (Time_played > 1) { Time_played = 1.0f; }
}

void GameMusic::stopMusic() {
	Time_played = 0.0f;
}

float GameMusic::getTimePlayed() { return Time_played; }
