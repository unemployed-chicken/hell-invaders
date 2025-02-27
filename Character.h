#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>

extern const float texure_update_per_second;
extern const bool debugging;

constexpr float character_scale{ 3.0f };
constexpr float demon_collision_whitespace_offset{ character_scale * .75f };
constexpr float demon_origin_whitespace_offset_x{ character_scale * .2f };
constexpr float demon_origin_whitespace_offset_y{ character_scale * .25f };


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
	int Attack_direction{};
	bool Is_projectile_ready{ false };


	// Texture Properties
	float Texture_update_rate = texure_update_per_second;
	float Last_texture_update{}; 
	float Width;
	float Height;
	float Scale{ character_scale };
	float Left_Right{ 1 }; 


public:
	Character(Texture2D character_texture, Texture2D projectile_texture, float pos_x, float pos_y, float speed, float attack_rate, int attack_direction);
	Texture2D getProjectileTexture();
	Texture2D getActiveTexture();
	int getAttackDirection();
	float getXCoordinate();
	float getYCoordinate();
	float getSpeed();
	float getLeftRight();
	float getWidth();
	float getHeight();
	//void bumpSpeed();
	void setSpeed(const float speed);
	void setIsProjectileReady(const bool b);
	void setTextureUpdateRate(float update_rate);
	void setTextureUpdateRate();


	/* 
	  These may not need to be virtual, but make based on demon
	*/
	virtual void render(); // Doesn't need to be virtual if you call setTexturePosition before calling Render
	virtual void setTexturePosition(); // Confirmed does need to be virtual

	// --------------------------------------------------------------

	virtual bool getIsProjectileReady();
	virtual Rectangle getCollisionRectangle();
	virtual void tick(const float dT);
	virtual void moveCharacter(const float dT);
};

