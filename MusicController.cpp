#include "MusicController.h"

MusicController::MusicController(float volume, bool is_music_on): Master_volume(volume), Is_music_on(is_music_on) {
	// Populates Mid_game_music_list
	generateMusic();

	// Start Music
	if (is_music_on) playCurrentMusic(false);
}

shared_ptr<Node<GamingMusic>> MusicController::getCurrentMusic() { return Current_music; }

void MusicController::setCurrentMusicToGameplayMusic() {
	Current_music->Data->restartMusic();
	Current_music = Mid_game_music_list.getHead();
	if (Is_music_on) {
		playCurrentMusic(true);
	}
}

void MusicController::playCurrentMusic(bool is_game_play) {
	PlayMusicStream(Current_music->Data->getSong());

	bool is_song_complete = Current_music->Data->playMusic();
	if (is_song_complete) { rotateMusic(is_game_play); }
}

void MusicController::reloadPropertyImpactedValues(Properties& properties) {
	Master_volume = properties.getFloatPropertyValue("Music_volume") / 100.f;
	Is_music_on = properties.getBoolPropertyValue("Is_music_on");
}

void MusicController::restartCurrentMusic() {
	Current_music->Data->restartMusic();
}

void MusicController::cleanUpMusic() {
	Main_screen_music->Data->cleanUpSong();
	Current_music = Mid_game_music_list.getHead();

	do {
		Current_music->Data->cleanUpSong();
		Current_music = Current_music->Next;
	} 
	while (Current_music != Mid_game_music_list.getHead());
}

void MusicController::rotateMusic(bool is_game_play) {
	Current_music->Data->restartMusic();
	if (is_game_play) Current_music = Current_music->Next;

	playCurrentMusic(is_game_play); // TODO: Confirm if I should playCurrentMusicHere
}

void MusicController::updateAllMusicVolume() {
	shared_ptr<Node<GamingMusic>> current_song = Mid_game_music_list.getHead();
	Main_screen_music->Data->reloadMusicVolume();

	do {
		current_song->Data->reloadMusicVolume();
		current_song = current_song->Next;
	} while (current_song != Mid_game_music_list.getHead());
}

//void MusicController::generateMidGameMusicList(map<string, GamingMusic>& music) {
//	Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(music["game_play_1"])));
//	Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(music["game_play_2"])));
//	Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(music["game_play_3"])));
//	Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(music["game_play_4"])));
//	Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(music["game_play_5"])));
//	Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(music["game_play_6"])));
//
//	Mid_game_music_list.getHead()->Previous = Mid_game_music_list.getTail();
//	Mid_game_music_list.getTail()->Next = Mid_game_music_list.getHead();
//}

void MusicController::generateMidGameMusicList() {
	// Add gameplay music to map in random order  
	// Keys determine the order music is played and remains constant. The music assigned to that key is randomized.  
	int numbs[6]{ 10,10,10,10,10,10 };

	int i = 0;
	while (i < 6) {
		int r = rand() % 6;
		bool already_in_numbs = false;

		// Check if index has already been used
		for (int x : numbs) {
			if (r == x) {
				already_in_numbs = true;
				break;
			}
		}

		// 
		if (!already_in_numbs) {
			numbs[i] = r;
			i++;

			Mid_game_music_list.insertAtEnd(make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(GamingMusic(LoadMusicStream(game_play_songs[r].c_str()), Master_volume))));
		}
	}
}


void MusicController::generateMusic() {
	Main_screen_music = make_shared<Node<GamingMusic>>(make_shared<GamingMusic>(GamingMusic(LoadMusicStream("audio\\main_screen.mp3"), Master_volume)));
	Current_music = Main_screen_music;

	generateMidGameMusicList();

	Mid_game_music_list.getHead()->Previous = Mid_game_music_list.getTail();
	Mid_game_music_list.getTail()->Next = Mid_game_music_list.getHead();
}