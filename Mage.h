#pragma once
#include "Character.h"

//extern float window_dimensions[2];
extern const bool debugging;

constexpr float starting_x_pos{ 320 };
constexpr float starting_y_pos{ 565 };
constexpr int attack_frames{ 9 }; // number of columns in the attack frame
constexpr int attack_texture_count{ 4 }; // The row of the attack animation

constexpr float mage_speed{ 200.f }; // pixels per second
constexpr float mage_fire_rate{ .25 }; // seconds per attack

constexpr int mage_textures_per_row{ 11 }; // number of rows in texture
constexpr int mage_textures_per_column{ 9 }; // number of columns in texture
constexpr Vector2 origin{ 43, 70 }; // Offsets the white space for movement
constexpr float collision_rec_white_space_off_set{ 1.5f }; // Offsets the white space for collision rectangle
constexpr float attack_texture_pixel_offset{ 3.5 }; // Offsets whitespace in texture when getting attack animation

class Mage : public Character {
	double score{};
	int lives{ 3 };
	bool Is_attacking{ false };
	bool Is_projectile_ready{ false };
	int Attack_frame{ 0 };
	

public:
	Mage(Texture2D character_texture, Texture2D projectile_texture);
	void render();
	void setTexturePosition();
	bool getIsProjectileReady();
	void setIsProjectileReady(const bool b);

	
	virtual Rectangle getCollisionRectangle() override;
	virtual void attack() override;
	virtual void moveCharacter(const float dT) override;
	virtual void tick(const float dT) override;
};

