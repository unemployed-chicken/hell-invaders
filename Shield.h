#pragma once
#include "raylib.h"
#include <map>
#include <string>
using std::map;
using std::string;

extern const bool debugging;

constexpr float Shield_width_scale{ 3 };
constexpr int Shield_height_scale{ 2 };
constexpr float Shield_starting_y_position{ 550 }; // ~ Screen Height - (Height of Mage + 5px)
constexpr float revive_shield_movement_speed{ -400 }; // pixels per second

class Shield {
protected:
	Texture2D Full_shield;
	Texture2D Mid_shield;
	Texture2D Low_shield;
	Texture2D Revive_shield;

	float Width;
	float Height;
	
	float X_coordinate;
	float Y_coordinate{ Shield_starting_y_position };
	
	float Width_scale{ Shield_width_scale };
	float Height_scale{ Shield_height_scale };
	int Damage_count{ 0 };
	bool Is_active{ true };
	bool Is_persistent{ false };


public:
	Shield(Texture2D full_shield, Texture2D mid_shield,	Texture2D low_shield, Texture2D revive_shield, float x_position);
	
	void takeDamage();
	void render();
	bool getIsActive();
	bool getIsPersistent();
	Rectangle getCollisionRectangle();

	virtual Texture2D getActiveTexture();
	virtual void tick(const float dT);
};

