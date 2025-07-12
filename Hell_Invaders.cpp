#include <iostream>
#include <filesystem>
#include<map>
#include "GameMap.h"
#include "Mage.h"
#include "raylib.h"
#include "raymath.h"
using std::map;
using std::string;


const string base_path{ "/Applications/Hell_Invaders/"};
// const string base_path{ "./Hell_Invaders_Mac_beta_Collin/"};


// DEBUGGING:
const bool debugging{ false };

// Window Properties
const float window_dimensions[2]{ 640.0f , 640.0f }; // Width * Height
const int targetFps{ 60 };

// General
const bool is_windows_os{ false };


// Function Declaration. Defined at the bottom of the page
map<string, Texture2D> generateTexture();
void cleanUpResources(map<string, Texture2D> textures);

int main() {
    srand(time(0));
    
    InitWindow(window_dimensions[0], window_dimensions[1], "Hell Invaders");
    InitAudioDevice();

    SetTargetFPS(targetFps);

    // Create Textures
    map<string, Texture2D> textures = generateTexture();
    GameMap map(textures);

    while (!WindowShouldClose() && !map.getIsEndGameRequested()) {
        BeginDrawing();
        ClearBackground(WHITE);

        bool t = !map.getIsMainScreen() && !map.getIsPropertiesScreen() && !map.getIsIntro();
        map.getMusicController().playCurrentMusic(t);

        if (map.getIsMainScreen()) {
            float menu_dT{ GetFrameTime() };
            map.displayHomeMenu(textures, menu_dT);
        }
        else if (map.getIsPropertiesScreen()) {
            float properties_dT{ GetFrameTime() };
            map.displayPropertiesMenu(textures, properties_dT);
        }
        else if (map.getIsGameOverScreen()) {
            // Draw Game Over
            float end_game_dt = GetFrameTime();
            bool go_to_home_screen = map.displayGameOverScreen(end_game_dt);
            if (go_to_home_screen) {
                map = GameMap(textures);
            }
        }
        else if (map.getIsIntro()) {
            // Run Intro Screen
            float practice_dT{ GetFrameTime() };
            map.tick(practice_dT);

            map.drawInstructions();

            if (IsKeyPressed(KEY_ENTER)) {
                map.getMusicController().setCurrentMusicToGameplayMusic();
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

    cleanUpResources(textures);
    map.getMusicController().cleanUpMusic();

    CloseAudioDevice();
    CloseWindow();
}


map<string, Texture2D> generateTexture() {
    string background_path = base_path;
	background_path.append("textures/Map/blue-with-stars.png");

    string midground_path = base_path;
	midground_path.append("textures/Map/mountains.png");

    string foreground_path = base_path;
	foreground_path.append("textures/Map/castle.png");

    string main_background_path_1 = base_path;
    main_background_path_1.append("textures/Map/home-background-1.png");

    string main_background_2 = base_path;
    main_background_2.append("textures/Map/home-background-2.png");

    string main_background_3 = base_path;
    main_background_3.append("textures/Map/home-background-3.png");

    string mage_path = base_path;
    mage_path.append("textures/Characters/MiniArchMage_no_outline.png");

    string magic_path = base_path;
    magic_path.append("textures/Projectiles/HumansProjectiles.png");

    string fire_path = base_path;
    fire_path.append("textures/Projectiles/fire.png");

    string full_shield_path = base_path;
    full_shield_path.append("textures/Projectiles/magic-shield-full.png");

    string revive_shield_path = base_path;
    revive_shield_path.append("textures/Projectiles/magic-shield-revive.png");
    
    string skull_path = base_path;
    skull_path.append("textures/Enemies/WarpSkull.png");

    string scamp_path = base_path;
    scamp_path.append("textures/Enemies/NefariousScamp.png");

    string fledge_path = base_path;
    fledge_path.append("textures/Enemies/FledglingDemon.png");

    string eye_path = base_path;
    eye_path.append("textures/Enemies/FloatingEye.png");

    return map<string, Texture2D> {
        { "background", LoadTexture(background_path.c_str()) },
        { "midground", LoadTexture(midground_path.c_str()) },
        { "foreground", LoadTexture(foreground_path.c_str()) },
        { "main_background_1", LoadTexture(main_background_path_1.c_str()) },
        { "main_background_2", LoadTexture(main_background_2.c_str()) },
        { "main_background_3", LoadTexture(main_background_3.c_str()) },
        { "mage", LoadTexture(mage_path.c_str())},
        { "magic", LoadTexture(magic_path.c_str()) },
        { "fire", LoadTexture(fire_path.c_str()) },
        { "full_shield", LoadTexture(full_shield_path.c_str()) },
        { "revive_shield", LoadTexture(revive_shield_path.c_str()) },
        { "skull", LoadTexture(skull_path.c_str()) },
        { "scamp", LoadTexture(scamp_path.c_str()) },
        { "fledge", LoadTexture(fledge_path.c_str()) },
        { "eye", LoadTexture(eye_path.c_str()) },
    };
}



void cleanUpResources(map<string, Texture2D> textures) {
	for (auto& texture : textures) {
		UnloadTexture(texture.second);
	}
}