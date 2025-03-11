#pragma once
#include "Character.h"
#include <iostream>

class Demon : public Character {
	int Points{ 100 };
	int Frame{ 0 };
	bool Is_down{ false };
	bool Is_first_down{ false };
	float elevation_change{};
	float attack_pause{};
	float attack_retry_rate{ 1.5 };

public:
	Demon(Texture2D character_texture, Texture2D projectile_texture, int demon_x_pos, int demon_y_pos, int texture_count, int points, float speed);
	~Demon();

	void setYCoordinate();
	void setTexturePosition();
	void setIsFirstDown(const bool b);
	void moveCharacter(const float dT);
	//void bumpSpeed();
	bool isProjectileReady();
	bool getIsFirstDown();
	int getPoints();
	float calculateXCoordinate(const float dT);

	virtual void tick(const float dT) override;
};


