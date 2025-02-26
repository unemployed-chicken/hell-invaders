#include <iostream>
#include<map>
#include "raylib.h"
#include "raymath.h"
#include "GameMap.h"
#include "Mage.h"
using std::map;
using std::string;


// DEBUGGING:
const bool debugging{ true };

// Window Properties
const float window_dimensions[2]{ 640.0f , 640.0f }; // Width * Height
const int targetFps{ 60 };


// Texture Properties
constexpr float texure_update_per_second{ 1.0f / 12.0f };

map<string, Texture2D> generateTexture();

int main() {
    srand(time(0));
    InitWindow(window_dimensions[0], window_dimensions[1], "Hell Invaders");
    SetTargetFPS(targetFps);

    // Create Textures
    map<string, Texture2D> textures = generateTexture();
    GameMap map(textures);
    map.generateShields();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        if (map.getMage().getLives() == 0 || map.hasInvaded()) {
            // Draw Game Over
            map.drawEndGame();
        }
        else {
            if (!map.hasDemons()) {
                map.generateDemonsList(textures);
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
        { "background", LoadTexture("textures\\Map\\space_background_pack\\Assets\\Blue Version\\layered\\blue-with-stars.png") },
        { "midground", LoadTexture("textures\\Map\\mountains.png") },
        { "foreground", LoadTexture("textures\\Map\\castle.png") },
        { "mage", LoadTexture("textures\\Characters\\MiniArchMage_no_outline.png")},
        { "magic", LoadTexture("textures\\Projectiles\\HumansProjectiles.png") },
        { "fire", LoadTexture("textures\\Projectiles\\fire.png") },
        { "full_shield", LoadTexture("textures\\Projectiles\\magic-shield-full.png") },
        { "mid_shield", LoadTexture("textures\\Projectiles\\magic-shield-medium.png") },
        { "low_shield", LoadTexture("textures\\Projectiles\\magic-shield-end.png") },
        { "revive_shield", LoadTexture("textures\\Projectiles\\magic-shield-revive.png") },
        { "skull", LoadTexture("textures\\Enemies\\WarpSkull.png") },
        { "scamp", LoadTexture("textures\\Enemies\\NefariousScamp.png") },
        { "fledge", LoadTexture("textures\\Enemies\\FledglingDemon.png") },
        { "eye", LoadTexture("textures\\Enemies\\FloatingEye.png") },

    };
}