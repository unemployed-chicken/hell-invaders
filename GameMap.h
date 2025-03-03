#pragma once

#include "Demon.h"
#include "DoubleLinkedList.h"
#include "Mage.h"
#include "Projectile.h"
#include "raylib.h"
#include "ReviveShield.h"
#include "Shield.h"
#include <vector>
#include <iostream>
#include <string>
#include <memory>
#include <map>
using std::vector;
using std::shared_ptr;
using std::map;
using std::string;
using std::make_shared;
using std::to_string;

extern const float window_dimensions[2];
extern const bool debugging;
extern const bool debuggingSpeedBump;

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
constexpr float shield_starting_x_coordinate{ 50 };
constexpr float shield_spacing{ 225 };
constexpr float demon_base_speed{ 50 }; // pixels per second 
constexpr float base_demon_points{ 50 };
constexpr float skull_points{ base_demon_points * 3 };
constexpr float fledge_points{ base_demon_points * 2 };
constexpr float scamp_points{ base_demon_points * 1 };
constexpr float special_demon_points{ base_demon_points * 10 };
constexpr int number_of_demon_textures{ 4 };
constexpr int number_of_rows_moved_per_speed_boost{ 3 };
constexpr int number_of_demon_columns{ 6 };
constexpr float speed_increase{ 10.0f };

const float demons_x_range[2]{ 5.0f, window_dimensions[1] - (16.f * character_scale) + 5.f}; // First is Left Limit, Second is Right Limit

class GameMap {
	Texture2D Background;
	Texture2D Midground;
	Texture2D Foreground;

	Texture2D Regular_shield;
	Texture2D Revive_shield;

	Mage mage;
	shared_ptr<Demon> Special_demon; // Can this be a unique_ptr?

	DoubleLinkedList<Projectile> Mage_projectiles{};
	DoubleLinkedList<Projectile> Demon_projectiles{};
	DoubleLinkedList<DoubleLinkedList<Demon>> Demons_columns{};
	DoubleLinkedList<Shield> Shields{};

	bool has_invaded{ false };
	bool has_special_demon_spawned{ false };
	int level{ 0 };
	int demons_moved_down_count{ 0 };
	
	bool hasCollision(shared_ptr<Demon> demon);
	void drawBackground();
	void drawLives();
	void drawShieldCount();
	void appendProjectile();
	void appendProjectile(shared_ptr<Demon> demon); 
	void moveMageProjectiles(const float dT);
	void moveDemonProjectiles(const float dT, Mage& mage);
	void moveAllDemons(const float dT);
	void allDemonCollisionCheckAndAppendDemonProjectiles();
	void checkDemonProjectileForMageProjectilesCollision(shared_ptr<Node<Projectile>> demon_projectiles);
	void checkDemonProjectilForShieldCollision(shared_ptr<Node<Projectile>> demon_projectiles);
	void drawAllShields();
	void mageTakesDamage();
	void generateOrMoveAllShields(const float dT);
	void generateReviveShield();
	void moveReviveShield(const float dT);
	void destroySpecialDemon(const bool is_killed);
	void moveDemonColumn(
		shared_ptr<Node<DoubleLinkedList<Demon>>> column,
		const float dT, 
		const bool is_first_down,
		const bool is_speed_bump
	);
	void demonColumnCollisionCheck(
		shared_ptr<Node<DoubleLinkedList<Demon>>> column
	);



public:
	GameMap(map<string, Texture2D> textures);
	//~GameMap();

	bool hasDemons();
	bool hasInvaded();
	bool getHasSpecialDemonInvaded();
	Mage& getMage();
	void tick(const float dT);
	void generateDemonsList(map<string, Texture2D> textures);
	void generateShields();
	void drawEndGame();
	void generateSpecialDemon(map<string, Texture2D> textures);
	void setHasSpecialDemonInvaded(bool b);
	void drawInstructions();
	int getDemonsMovedDownCount();
};

