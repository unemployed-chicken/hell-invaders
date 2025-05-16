#include "GamingMusic.h"

//GamingMusic::GamingMusic(Music song, string name) : Song(song), Name(name){}
GamingMusic::GamingMusic(Music song, float volume) : Song(song), Volume(volume){
	SetMusicVolume(Song, Volume);
}
GamingMusic::GamingMusic() {}

bool GamingMusic::playMusic() {
	UpdateMusicStream(Song);
	float current_time_played = GetMusicTimePlayed(Song) / GetMusicTimeLength(Song);
	if (current_time_played < Time_played) {
		return true;
	}
	Time_played = current_time_played;
	return false;
}

void GamingMusic::stopMusic() {
	StopMusicStream(Song); 
	Time_played = 0.0f;
}
void GamingMusic::reloadMusicVolume() { 
	SetMusicVolume(Song, Volume); 
}
void GamingMusic::setVolume(float volume) { Volume = volume; }
void GamingMusic::cleanUpSong() { UnloadMusicStream(Song); }
float GamingMusic::getTimePlayed() { return Time_played; }
bool GamingMusic::getIsOn() { return Is_on; }
Music GamingMusic::getSong() { return Song; }
