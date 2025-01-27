#pragma once
#include "Character.h"

//extern float window_dimensions[2];

constexpr float starting_x_pos{ 320 };
constexpr float starting_y_pos{ 565 };

class Mage : public Character {
	double score{};
	int lives{ 3 };

public:
	Mage(Texture2D texture);
	virtual void moveCharacter(float dT) override;
	void render();
	virtual Rectangle getCollisionRectangle() override;
};

