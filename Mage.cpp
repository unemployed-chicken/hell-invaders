#include "Mage.h"
#include <iostream>



Mage::Mage(Texture2D character_texture, Texture2D projectile_texture) : 
	Character(character_texture, projectile_texture, starting_x_pos, starting_y_pos, mage_speed, mage_fire_rate, -1) {
	Width = static_cast<float>(character_texture.width) / mage_textures_per_row;
	Height = static_cast<float>(character_texture.width) / mage_textures_per_column;
};

bool Mage::getIsProjectileReady() { return Is_projectile_ready; }
void Mage::setIsProjectileReady(const bool b) { Is_projectile_ready = b; }

void Mage::moveCharacter(const float dT) {
	if (IsKeyDown(KEY_LEFT)) {
		Left_Right = -1;
		if (X_coordinate - Speed * dT < 0) {
			X_coordinate = 0;
		}
		else {
			X_coordinate -= Speed * dT;
		}
	};
	if (IsKeyDown(KEY_RIGHT)) {
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
	if (!Is_attacking) {
		Attack_cooldown += dT;
		moveCharacter(dT);
		attack();
	}
	else {
		Last_texture_update += dT;
		
		// Update Current Character Frame
		if (Last_texture_update >= Texture_update_rate) {
			Attack_frame++;
			Last_texture_update = 0.0f;
		}

		// If attack phase complete, reset all values
		if (Attack_frame == attack_frames) {
			Attack_frame = 0;
			Is_attacking = false;
		}
	}
}


void Mage::render() {
	setTexturePosition();
	Rectangle source{ Texture_position.x, Texture_position.y, Width * Left_Right, Height };
	Rectangle destination{ X_coordinate, Y_coordinate, Scale * Width, Scale * Height };
	
	// Temporary for now:
	Rectangle collision_rectangle = getCollisionRectangle();

	DrawTexturePro(Active_texture, source, destination, origin, 0.0f, WHITE);
	if (debugging) { 
		DrawRectangleLines(collision_rectangle.x, collision_rectangle.y, collision_rectangle.width, collision_rectangle.height, RED); 
	};
}

void Mage::setTexturePosition() {
	// Set Texture Position
	Texture_position.x = Width * Attack_frame; // This works because Attack_frame will be 0 if false 
	
	Is_attacking ? Texture_position.y = ( Height * attack_texture_count) + attack_texture_pixel_offset : Texture_position.y = 0; 
}


Rectangle Mage::getCollisionRectangle(){
	return Rectangle{ 
		X_coordinate,	
		Y_coordinate, 
		Width * collision_rec_white_space_off_set, 
		Height * collision_rec_white_space_off_set 
	};
}

void Mage::attack(){ // To return a projectile and pass an array or vector of projectiles
	if (IsKeyPressed(KEY_SPACE) && Attack_cooldown >= Attack_rate) {
		Attack_cooldown = 0.0f;
		Is_attacking = true;
		Is_projectile_ready = true;
	}
}


