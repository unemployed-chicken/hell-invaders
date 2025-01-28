#pragma once
#include "raylib.h"

extern const float texure_update_per_second;

constexpr float projectile_speed{ 400.f };
constexpr float projectile_scale{ 4.0f };

class Projectile{
	Texture2D Texture;
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

	float Velocity; // Mage attack is negative -1, Demon attack is +1
	Rectangle Collision_rectangle{};

public:
	Projectile(Texture2D texture, int number_of_objects_in_x, int number_of_objects_in_y, float x_pos, float y_pos, int direction);
	//~Projectile();

	void tick(float dT);
	void render();
};

