#include <iostream>
#include<map>
#include "raylib.h"
#include "raymath.h"
#include "GameMap.h"
#include "Mage.h"
#include "Demon.h" // Remove later as this is moved to GameMap
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
    Demon test1{ textures["skull"], textures["fire"], 100, 0, 4 }; 
    Demon test2{ textures["scamp"], textures["fire"], 100, 50, 4 };
    Demon test3{ textures["fledge"], textures["fire"], 100, 100, 4 };
    Demon test4{ textures["eye"], textures["fire"], 100, 150, 4 };


    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        float dT{ GetFrameTime() };

        if (test1.getXCoordinate() + (test1.getSpeed() * test1.getLeftRight() * dT) < 0 ||
            test1.getXCoordinate() + (test1.getSpeed() * test1.getLeftRight() * dT) > 625 - test1.getWidth())
        {
            test1.setIsDown(true);
        }

        if (test2.getXCoordinate() + (test2.getSpeed() * test2.getLeftRight() * dT) < 0 ||
            test2.getXCoordinate() + (test2.getSpeed() * test2.getLeftRight() * dT) > 625 - test2.getWidth())
        {
            test2.setIsDown(true);
        }
        if (test3.getXCoordinate() + (test3.getSpeed() * test3.getLeftRight() * dT) < 0 ||
            test3.getXCoordinate() + (test3.getSpeed() * test3.getLeftRight() * dT) > 625 - test3.getWidth())
        {
            test3.setIsDown(true);
        }

        if (test4.getXCoordinate() + (test4.getSpeed() * test4.getLeftRight() * dT) < 0 ||
            test4.getXCoordinate() + (test4.getSpeed() * test4.getLeftRight() * dT) > 625 - test4.getWidth())
        {
            test4.setIsDown(true);
        }

        // Move Character
        mage.tick(dT);
        
        // Move and Draw all Projectiles and Demons
        map.tick(dT, mage);

        test1.tick(dT);
        test2.tick(dT);
        test3.tick(dT);
        test4.tick(dT);


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
        { "fire", LoadTexture("textures\\Projectiles\\Fire_Spreadsheet.png") },
        { "skull", LoadTexture("textures\\Enemies\\WarpSkull.png") },
        { "scamp", LoadTexture("textures\\Enemies\\NefariousScamp.png") },
        { "fledge", LoadTexture("textures\\Enemies\\FledglingDemon.png") },
        { "eye", LoadTexture("textures\\Enemies\\FloatingEye.png") },

    };
}