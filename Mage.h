#pragma once
#include "Character.h"

//extern float window_dimensions[2];

constexpr float starting_x_pos{ 320 };
constexpr float starting_y_pos{ 565 };
constexpr int attack_frames{ 9 };

class Mage : public Character {
	double score{};
	int lives{ 3 };
	bool Is_attacking{ false };
	int Attack_frame{ 0 };

public:
	Mage(Texture2D character_texture, Texture2D projectile_texture);
	void render();
	void setTexturePosition();
	
	virtual Rectangle getCollisionRectangle() override;
	virtual void attack() override;
	virtual void moveCharacter(float dT) override;
	virtual void tick(float dT) override;
};

