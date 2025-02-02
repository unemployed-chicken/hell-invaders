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
constexpr float texure_update_per_second{ 1.0f / 12.0f }; // Make this viewable in all files later



map<string, Texture2D> generateTexture();

int main() {
    InitWindow(window_dimensions[0], window_dimensions[1], "Hell Invaders");
    SetTargetFPS(targetFps);

    // Create Textures
    map<string, Texture2D> textures = generateTexture();
    GameMap map(textures["background"], textures["midground"], textures["foreground"]);

    // Create Character
    Mage mage{ textures["mage"], textures["magic"]};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        float dT{ GetFrameTime() };

        // Move Character
        mage.tick(dT);
        
        // Move and Draw all Projectiles and Demons
        map.tick(dT, mage);

        // Draw Mate
        mage.render();

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
    };
}