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
constexpr float revive_shield_movement_speed{ -600 }; // pixels per second

class Shield {
protected:
	Texture2D Shield_Texture;

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
	Shield(Texture2D shield, float x_position);
	
	void takeDamage();
	void render();
	bool getIsActive();
	bool getIsPersistent();
	Rectangle getCollisionRectangle();

	virtual Color getShieldColor();
	virtual void tick(const float dT);
};

