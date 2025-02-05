#pragma once
#include "raylib.h"
#include <iostream>

extern const float texure_update_per_second;
extern const float window_dimensions[2];
extern const bool debugging;

constexpr float magic_projectile_speed{ 300.f };
constexpr float fire_projectile_speed{ 150.f };
constexpr float projectile_scale{ 4.0f };

class Projectile{
	Texture2D Active_texture;
	Vector2 Texture_position{};
	int frame{};
	int Number_of_objects_in_x;
	int Number_of_objects_in_y;
	
	float X_coordinate;
	float Y_coordinate;

	float Texture_update_rate = texure_update_per_second;
	float Last_texture_update{};
	float Width;
	float Height;
	float Scale{ projectile_scale };
	float Rotation{};

	float Collision_rec_white_space_offset_x;
	float Collision_rec_white_space_offset_y;
	float Collision_rec_scale_x;
	float Collision_rec_scale_y;

	float Velocity; // Mage attack is negative -1, Demon attack is +1
	Rectangle Collision_rectangle{};
	bool Is_active{ true };
	bool Is_magic;

public:
	Projectile(
		Texture2D texture, int number_of_objects_in_x, int number_of_objects_in_y, float x_pos, 
		float y_pos, int direction, float collision_rec_offset_x, float collision_rec_offset_y, 
		float collision_rec_scale_x, float collision_rec_scale_y, float rotation = 0.0f, bool isMagic = false);
	~Projectile();

	void setIsActive(bool boolean);
	bool getIsActive();
	void tick(const float dT);
	void render();
	float getYCoordinate();
	void setTexturePosition();
	void setRotation(float rotation);
	Rectangle getCollisionRectangle();
	void setXCoordinate();
	void setIsActiveToFalse();
};

