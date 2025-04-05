#include <iostream>
#include<map>
#include "GameMap.h"
#include "Mage.h"
#include "raylib.h"
#include "raymath.h"
using std::map;
using std::string;


// DEBUGGING:
const bool debugging{ false };

// Window Properties
const float window_dimensions[2]{ 640.0f , 640.0f }; // Width * Height
const int targetFps{ 60 };

// General
const bool is_windows_os{ true };
constexpr int end_game_screen_pause_time{ 10 }; // seconds

const string game_play_songs[6]{
    "audio\\metal-headed.mp3", "audio\\fierce.mp3", "audio\\doom-extreme-metal-rock.mp3",
    "audio\\metal-header.mp3", "audio\\rise-of-the-zombies.mp3", "audio\\we-can-win.mp3"
};


// Function Declaration. Defined at the bottom of the page
map<string, Texture2D> generateTexture();
map<string, GamingMusic> generateMusic();
void cleanUpResources(map<string, Texture2D> textures, map<string, GamingMusic> music);

int main() {
    srand(time(0));
    
    InitWindow(window_dimensions[0], window_dimensions[1], "Hell Invaders");
    InitAudioDevice();

    SetTargetFPS(targetFps);

    float time_on_screen{};
	float timePlayed{ 0.0f };

    // Create Textures
    map<string, Texture2D> textures = generateTexture();
	map<string, GamingMusic> music = generateMusic();
    GameMap map(textures, music);

    while (!WindowShouldClose() && !map.getIsEndGameRequested()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (map.getIsMainScreen()) {
            float menu_dT{ GetFrameTime() };
            map.displayHomeMenu(textures, menu_dT);
        }
        else if (map.getIsPropertiesScreen()) {
            float properties_dT{ GetFrameTime() };
            map.displayPropertiesMenu(textures, properties_dT);
        }
        else if (map.getMage().getLives() == 0 || map.hasInvaded()) {
            // Draw Game Over
            time_on_screen += GetFrameTime();
            if (map.getCurrentMusic()) { map.getCurrentMusic()->Data->playMusic(); }
            map.drawEndGame();
            if (time_on_screen >= end_game_screen_pause_time) { 
                time_on_screen = 0;
                map = GameMap(textures, music); 
            }
        }
        else if (map.getIsIntro()) {
            // Run Intro Screen
            float practice_dT{ GetFrameTime() };
            map.tick(practice_dT);

            map.drawInstructions();

            if (IsKeyPressed(KEY_ENTER)) {
                map.setCurrentMusicToGameplayMusic();
                map.clearAllShields();
                map.setResetShieldCountToStartingAmount();
                map.setIsIntro(false);
                if (map.getPropertiesShouldStartGameWithShieldsActive()) { map.generateShields(); }
            }
        }
        else {
            if (!map.hasDemons()) {
                map.setHasSpecialDemonInvaded(false);
                map.generateDemonsList(textures);
            }

            if (!map.getHasSpecialDemonInvaded() && map.getDemonsMovedDownCount() > 2 ) {
                int x = rand() % 10000;
                if (x <= 10) { map.generateSpecialDemon(textures); }
                if (debugging) { std::cout << "Random Number % 10000: " << x << '\n'; }
            }

            // Create last update time
            float dT{ GetFrameTime() };

            // Move and Draw all Objects
            map.tick(dT);
        }

        EndDrawing();
    }

	cleanUpResources(textures, music); 

    CloseAudioDevice();
    CloseWindow();
}


map<string, Texture2D> generateTexture() {
    return map<string, Texture2D> {
        { "background", LoadTexture("textures\\Map\\blue-with-stars.png") },
        { "midground", LoadTexture("textures\\Map\\mountains.png") },
        { "foreground", LoadTexture("textures\\Map\\castle.png") },
        { "main_background_1", LoadTexture("textures\\Map\\home-background-1.png") },
        { "main_background_2", LoadTexture("textures\\Map\\home-background-2.png") },
        { "main_background_3", LoadTexture("textures\\Map\\home-background-3.png") },
        { "mage", LoadTexture("textures\\Characters\\MiniArchMage_no_outline.png")},
        { "magic", LoadTexture("textures\\Projectiles\\HumansProjectiles.png") },
        { "fire", LoadTexture("textures\\Projectiles\\fire.png") },
        { "full_shield", LoadTexture("textures\\Projectiles\\magic-shield-full.png") },
        { "revive_shield", LoadTexture("textures\\Projectiles\\magic-shield-revive.png") },
        { "skull", LoadTexture("textures\\Enemies\\WarpSkull.png") },
        { "scamp", LoadTexture("textures\\Enemies\\NefariousScamp.png") },
        { "fledge", LoadTexture("textures\\Enemies\\FledglingDemon.png") },
        { "eye", LoadTexture("textures\\Enemies\\FloatingEye.png") },
    };
}

map<string, GamingMusic> generateMusic() {  
   // Create music map with constants  
   map<string, GamingMusic> loaded_music = {};  
   loaded_music["main_screen"] = GamingMusic(LoadMusicStream("audio\\main_screen.mp3"), "main_screen");  
   loaded_music["end_game"] = GamingMusic(LoadMusicStream("audio\\end_game.mp3"), "end_game");  

   // Add gameplay music to map in random order  
   // Keys determine the order music is played and remains constant. The music assigned to that key is randomized.  
   int numbs[6]{10,10,10,10,10,10};  

   int i = 0;  
   while (i < 6) {  
       int r = rand() % 6;
       bool already_in_numbs = false;  
       for (int x : numbs) {  
           if (r == x) {  
               already_in_numbs = true;  
               break;  
           }  
       }  

       if (!already_in_numbs) {  
           numbs[i] = r;  
           i++;  
           string name = "game_play_";  
           name.append(to_string(i));
           loaded_music[name] = GamingMusic(LoadMusicStream(game_play_songs[r].c_str()), name);  
       }  
   }  

   return loaded_music;  
}


void cleanUpResources(map<string, Texture2D> textures, map<string, GamingMusic> music) {
	for (auto& texture : textures) {
		UnloadTexture(texture.second);
	}

	for (auto& music : music) {
		UnloadMusicStream(music.second.getSong());
	}
}