#pragma once

#include "DoubleLinkedList.h"
#include "raylib.h"
#include "Projectile.h"
#include "Mage.h"
#include "Demon.h"
#include <vector>
#include <iostream>
#include <memory>
#include <map>
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::map;
using std::string;

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
constexpr float end_game_coordinates_offset[2]{.15, .40};
constexpr float end_game_text_size{ 75 };

const float demons_x_range[2]{ 5.0f, window_dimensions[1] - (16.f * character_scale) + 5.f}; // First is Left Limit, Second is Right Limit




class GameMap {
	Texture2D Background;
	Texture2D Midground;
	Texture2D Foreground;

	DoubleLinkedList<Projectile> Mage_projectiles{};
	DoubleLinkedList<Projectile> Demon_projectiles{};
	DoubleLinkedList<DoubleLinkedList<Demon>> Demons_columns{};

	void drawBackground();
	void appendProjectile(Mage& mage);
	void appendProjectile(Demon& demon); // to be created later
	void moveMageProjectiles(const float dT);
	void moveDemonProjectiles(const float dT, Mage& mage);
	void moveAllDemons(const float dT);
	void moveDemonColumn(
		shared_ptr<Node<DoubleLinkedList<Demon>>> column,
		const float dT, 
		const bool is_down
	);
	void allDemonCollisionCheckAndAppendDemonProjectiles();
	void demonColumnCollisionCheck(
		shared_ptr<Node<DoubleLinkedList<Demon>>> column
	);
	bool hasCollision(Demon& demon);
	void checkDemonProjectileForMageProjectileCollisions(shared_ptr<Node<Projectile>> demon_projectiles);



public:
	GameMap(map<string, Texture2D> textures);
	//~GameMap();

	void tick(const float dT, Mage &mage);
	void generateDemonsList(map<string, Texture2D> textures);
	void drawEndGame();
};

