#include <iostream>
#include<map>
#include "raylib.h"
#include "raymath.h"
#include "Mage.h"
using std::map;
using std::string;

// Window Properties
const float window_dimensions[2]{ 640.0f , 640.0f }; // Width * Height
const int targetFps{ 60 };

// Backgrounds Properties
const float background_scale{ 3.0f };
const float midground_scale{ 3.0f };
const float foreground_scale{ 1.1f };

const Vector2 background_pos{ -25.0f, 0.0f };
const Vector2 midground_pos{ 0.0f, -50.0f };
const Vector2 foreground_pos{ -30.0f, 390 };

// Texture Properties
constexpr float texure_update_per_second{ 1.0f / 12.0f }; // Make this viewable in all files later



map<string, Texture2D> generateTexture();
void drawBackground(map<string, Texture2D> textures);


int main() {
    InitWindow(window_dimensions[0], window_dimensions[1], "Hell Invaders");
    SetTargetFPS(targetFps);


    // Create Textures
    map<string, Texture2D> textures = generateTexture();

    // Create Character
    Mage mage{ textures["mage"], textures["magic"]};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        float dT{ GetFrameTime() };

        drawBackground(textures);
        mage.tick(dT);
        mage.render();

        EndDrawing();
    }

    CloseWindow();
}


void drawBackground(map<string, Texture2D> textures) {
    DrawTextureEx(textures["background"], background_pos, 0.0, background_scale, WHITE);
    DrawTextureEx(textures["midground"], midground_pos, 0.0, midground_scale, WHITE);
    DrawTextureEx(textures["foreground"], foreground_pos, 0.0, foreground_scale, WHITE);
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