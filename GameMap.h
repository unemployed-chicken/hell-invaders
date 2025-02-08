#pragma once

#include "DoubleLinkedList.h"
#include "raylib.h"
#include "Projectile.h"
#include "Mage.h"
#include <vector>
#include <iostream>
#include <memory>
using std::vector;
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;

extern const float window_dimensions[2];
extern const bool debugging;

// Backgrounds Properties
const float background_scale{ 3.0f };
const float midground_scale{ 3.0f };
const float foreground_scale{ 1.1f };

const Vector2 background_pos{ -25.0f, 0.0f };
const Vector2 midground_pos{ 0.0f, -50.0f };
const Vector2 foreground_pos{ -30.0f, 390 };

constexpr float mage_projectile_collision_offset_x{ 24.0 };
constexpr float mage_projectile_collision_offset_y{ -31.0 };
constexpr float mage_projectile_collision_scale_x{ 1.5 };
constexpr float mage_projectile_collision_scale_y{ 2.0 };
constexpr float mage_projectile_rotation{ -90.0 };




class GameMap {
	Texture2D Background;
	Texture2D Midground;
	Texture2D Foreground;

	DoubleLinkedList<Projectile> Projectiles{};
	


public:
	GameMap(Texture2D background, Texture2D midground, Texture2D foreground);
	//~GameMap();

	void appendProjectile(Mage& mage);
	//void appendProjectile(Demon& demon); // to be created later
	void tick(float dT, Mage &mage);
	void drawBackground();
	//void removeProjectile(); // This shouldn't be needed
};

