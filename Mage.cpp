#include "Mage.h"
#include <iostream>



Mage::Mage(Texture2D character_texture, Texture2D projectile_texture) : 
	Character(character_texture, projectile_texture, starting_x_pos, starting_y_pos, mage_speed, mage_fire_rate, -1) {
	Width = static_cast<float>(character_texture.width) / mage_textures_per_row;
	Height = static_cast<float>(character_texture.width) / mage_textures_per_column;
}


int Mage::getLives() { return Lives; }
bool Mage::getIsHurt() { return Is_hurt; }
int Mage::getScore() { return Score; }
int Mage::getShieldCount() { return Shield_count; }
int Mage::getTextureFrame() { return Texture_frame; }
bool Mage::getIsShieldReady() {	return Is_shield_ready && Texture_frame == 5; }
bool Mage::getIsPostReviveActive() { return Is_post_revive_active; }
bool Mage::getIsReviveShieldActive() { return Is_revive_shield_active; }
bool Mage::getIsProjectileReady() { return Is_projectile_ready && Texture_frame == 5; }
void Mage::addScore(const int points) { Score += points; }
void Mage::decrementShieldCount() { --Shield_count; }
void Mage::incrementShieldCount() { ++Shield_count; }
void Mage::setShieldCountToStartingAmount() { Shield_count = number_of_starting_shields; }
void Mage::setIsShieldReady(const bool b) { Is_shield_ready = b; }
void Mage::setIsReviveShieldActive(const bool b) { Is_revive_shield_active = b; }

void Mage::takeDamage() {
	Last_texture_update = 0.0f;
	Is_hurt = true;
	Lives--;
	Texture_frame = 0;
	Is_attacking = false;
	setTextureUpdateRate();
}


void Mage::moveCharacter(const float dT) {
	if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
		Left_Right = -1;
		if (X_coordinate - Speed * dT < 0) {
			X_coordinate = 0;
		}
		else {
			X_coordinate -= Speed * dT;
		}
	};
	if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
		Left_Right = 1;
		if (X_coordinate + Speed * dT > 625 - Width) { // TODO: 625 offsets the witespace of the texture
			X_coordinate = 625 - Width;
		}
		else {
			X_coordinate += Speed * dT;
		}
	};
}

void Mage::tick(const float dT) {
	if (Is_hurt) {
		Last_texture_update += dT;

		if (Last_texture_update >= Texture_update_rate) {
			Texture_frame++;
			Last_texture_update = 0.0f;
		}

		if (Texture_frame == death_frames) {
			if (Death_count_pause < death_count_frame_pause) {
				Death_count_pause++;
				Texture_frame--;
			}
			else {
				Death_count_pause = 0;
				Texture_frame = 0;
				Is_hurt = false;
				Is_post_revive_active = true;
			}

		}
	}
	else if (Is_post_revive_active) {
		Last_texture_update += dT;

		if (!Is_revive_shield_active && Texture_frame == 0) {
			Is_revive_shield_active = true;
			castShield(true);
		}

		if (!(Texture_frame == 3 && Is_revive_shield_active)) {
			if (Last_texture_update >= Texture_update_rate) {
				Texture_frame++;
				Last_texture_update = 0.0f;
			}
			if (Texture_frame == casting_frames) {
				Texture_frame = 0;
				Is_casting_shield = false;
				Is_post_revive_active = false;
			}
		}


	}
	else if (Is_attacking || Is_casting_shield) {
		Last_texture_update += dT;

		// Update Current Character Frame
		if (Last_texture_update >= Texture_update_rate) {
			Texture_frame++;
			Last_texture_update = 0.0f;
		}

		// If attack phase complete, reset all values
		if (Is_attacking && Texture_frame == attack_frames) {
			Texture_frame = 0;
			Is_attacking = false;
			setTextureUpdateRate();
		}
		// If casting phase complete, reset all values
		else if (Is_casting_shield && Texture_frame == casting_frames) {
			Texture_frame = 0;
			Is_casting_shield = false;
		}
	}
	else {
		Attack_cooldown += dT;
		moveCharacter(dT);
		attack();
		castShield();
	}
}


void Mage::render() {
	setTexturePosition();
	Rectangle source{ Texture_position.x, Texture_position.y, Width * Left_Right, Height };
	Rectangle destination{ X_coordinate, Y_coordinate, Scale * Width, Scale * Height };
	
	Rectangle collision_rectangle = getCollisionRectangle();

	DrawTexturePro(Active_texture, source, destination, origin, 0.0f, WHITE);
	if (debugging) { 
		DrawRectangleLines(collision_rectangle.x, collision_rectangle.y, collision_rectangle.width, collision_rectangle.height, RED); 
	};
}

void Mage::setTexturePosition() {
	// Set Texture Position
	Texture_position.x = Width * Texture_frame;

	if (Is_hurt) {
		Texture_position.y = (Height * death_texture_count) + death_texture_pixel_offset;
	}
	else if (Is_attacking) {
		Texture_position.y = (Height * attack_texture_count) + attack_texture_pixel_offset;
	}
	else if (Is_casting_shield || Is_post_revive_active) {
		Texture_position.y = (Height * casting_texture_count) + casting_texture_pixel_offset;
	}
	else {
		Texture_position.y = 0;
	}
}

Rectangle Mage::getCollisionRectangle(){
	return Rectangle{ 
		X_coordinate,	
		Y_coordinate, 
		Width * collision_rec_white_space_off_set, 
		Height * collision_rec_white_space_off_set 
	};
}

void Mage::attack() { 
	bool wants_to_attack = IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W);
	if (wants_to_attack && Attack_cooldown >= Attack_rate) {
		Attack_cooldown = 0.0f;
		Is_attacking = true;
		Is_projectile_ready = true;
		setTextureUpdateRate(attack_texture_update_rate_per_second);
	}
}

void Mage::castShield() {
	castShield(IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_S));
}

void Mage::castShield(bool wants_to_cast_shield) {
	if (wants_to_cast_shield && Shield_count > 0) {
		Is_casting_shield = true;
		Is_shield_ready = true;
	}
}


