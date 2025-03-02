#pragma once
#include "Character.h"

extern const bool debugging;

constexpr float starting_x_pos{ 320 };
constexpr float starting_y_pos{ 582 };
constexpr int attack_frames{ 9 }; // number of columns in the attack animation
constexpr int attack_texture_count{ 4 }; // The row of the attack animation
constexpr int death_frames{ 9 }; // number of columns in the death animation
constexpr int death_texture_count{ 6 }; // The row of the death animation
constexpr int casting_frames{ 10 }; // number of columns in the casting animation
constexpr int casting_texture_count{ 5 }; // The row of the death animation

constexpr float attack_texture_update_rate_per_second{ 1.0f / 18.0f };
constexpr float mage_speed{ 200.f }; // pixels per second
constexpr float mage_fire_rate{ .15 }; // seconds per attack

constexpr int mage_textures_per_row{ 11 }; // number of rows in texture
constexpr int mage_textures_per_column{ 9 }; // number of columns in texture
constexpr Vector2 origin{ 34, 55 }; // Offsets the white space for movement

constexpr float collision_rec_white_space_off_set{ character_scale / 3.f }; // Offsets the white space for collision rectangle

constexpr float casting_texture_pixel_offset{ -3.5 }; // Offsets whitespace in texture when getting casting animation
constexpr float attack_texture_pixel_offset{ 3.5 }; // Offsets whitespace in texture when getting attack animation
constexpr float death_texture_pixel_offset{ 20.45 }; // Offsets whitespace in texture when getting death animation
constexpr float death_count_frame_pause{ 9 }; // Number of times to repeat final death stage frames

class Mage : public Character {
	int Score{};
	int Lives{ 3 };
	int Shield_count{ 3 };
	int Texture_frame{ 0 };
	int Death_count_pause{ 0 };
	bool Is_attacking{ false };
	bool Is_hurt{ false };
	bool Is_casting_shield{ false };
	bool Is_shield_ready{ false };
	bool Is_post_revive_active{ false };
	bool Is_revive_shield_active{ false };
	

public:
	Mage(Texture2D character_texture, Texture2D projectile_texture);

	int getLives();
	int getScore();
	int getShieldCount();
	int getTextureFrame();
	bool getIsHurt();
	bool getIsShieldReady();
	bool getIsPostReviveActive();
	bool getIsReviveShieldActive();
	void addScore(const int points);
	void attack();
	void castShield();
	void castShield(bool wants_to_cast_shield);
	void takeDamage();
	void decrementShieldCount();
	void incrementShieldCount();
	void setIsShieldReady(bool b);
	void setIsReviveShieldActive(bool b);

	virtual void render();
	virtual void setTexturePosition();
	
	virtual bool getIsProjectileReady() override;
	virtual Rectangle getCollisionRectangle() override;
	virtual void moveCharacter(const float dT) override;
	virtual void tick(const float dT) override;
};

