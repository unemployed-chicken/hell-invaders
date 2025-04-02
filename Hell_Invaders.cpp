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
constexpr int end_game_screen_pause_time{ 3 }; // seconds

// Declares generateTexture() in Hell_Invaders.cpp.
map<string, Texture2D> generateTexture();

int main() {
    srand(time(0));
    InitWindow(window_dimensions[0], window_dimensions[1], "Hell Invaders");
    SetTargetFPS(targetFps);

    float time_on_screen{};

    // Create Textures
    map<string, Texture2D> textures = generateTexture();
    GameMap map(textures);

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
            map.drawEndGame();
            if (time_on_screen >= end_game_screen_pause_time) { 
                time_on_screen = 0;
                map = GameMap(textures); 
            }
        }
        else if (map.getIsIntro()) {
            // Run Intro Screen
            float practice_dT{ GetFrameTime() };
            map.tick(practice_dT);

            map.drawInstructions();

            if (IsKeyPressed(KEY_ENTER)) {
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
