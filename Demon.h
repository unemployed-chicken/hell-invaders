#pragma once
#include "Character.h"
#include <iostream>

const float demon_speed{ 100 }; // These will need to change as a new level appears. Figure this out later
const float demon_fire_rate{ .25 }; // These will need to change as a new level appears. Figure this out later

class Demon : public Character {
	int points{ 100 };
	int Frame{ 0 };
	bool Is_down{ false };
	bool Is_first_down{ false };
	float elevation_change{};

public:
	Demon(Texture2D character_texture, Texture2D projectile_texture, int demon_x_pos, int demon_y_pos, int texture_count);
	//Demon();
	~Demon();

	void setYCoordinate();
	void setTexturePosition();
	void setIsFirstDown(const bool b);
	float calculateXCoordinate(const float dT);
	void moveCharacter(const float dT);
	void calculateIsProjectileReady();

	virtual void attack() override;
	virtual void tick(const float dT) override;
};

