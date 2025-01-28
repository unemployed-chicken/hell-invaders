#pragma once
#include "raylib.h"
#include "raymath.h"

extern const float texure_update_per_second;


//constexpr float texure_update_per_second{ 1.0f / 12.0f };
constexpr float character_scale{ 4.0f };


class Character {
protected:
	Texture2D Active_texture;
	Vector2 Texture_position{};
	float X_coordinate;
	float Y_coordinate;

	Texture2D Projectile_texture;

	// Gameplay Properties
	float Speed;
	float Attack_rate;
	float Attack_cooldown{};

	// Texture Properties
	float Texture_update_rate = texure_update_per_second;
	float Last_texture_update{}; 
	float Width;
	float Height;
	float Scale{ character_scale };
	float Left_Right{ 1 }; 


public:
	Character(Texture2D character_texture, Texture2D projectile_texture, float pos_x, float pos_y, float speed, float attack_rate);
	virtual void moveCharacter(float dT);
	//virtual void takeDamage();

	//void attack();
	void render();
	virtual Rectangle getCollisionRectangle();
	virtual void attack();
	virtual void tick(float dT);
};

