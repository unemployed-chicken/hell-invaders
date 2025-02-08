#include "Demon.h"


Demon::Demon(Texture2D character_texture, Texture2D projectile_texture, int demon_x_pos, int demon_y_pos, int texture_count) :
	Character(character_texture, projectile_texture, demon_x_pos, demon_y_pos, demon_speed, demon_fire_rate, 1) {
	Width = static_cast<float>(character_texture.width) / texture_count;
	Height = static_cast<float>(character_texture.height);
	// Temp for testing:
	Texture_update_rate *= 2;
}
Demon::~Demon() {
	std::cout << "Destroying Demon" << '\n';
}

void Demon::attack(){}

void Demon::tick(const float dT) {
	Last_texture_update += dT;
	if (Last_texture_update >= Texture_update_rate) {
		Frame++;
		Last_texture_update = 0.0f;
	}

	// MoveCharacter
	moveCharacter(dT);
	
	// Do Collision check for all projectiles // Performed on map side // This may be changes to just User projectiles 
	
	// setTexturePosition
	setTexturePosition();

	// Render Character
	render();

	// Determine if this frame is an attack (applicable to only front demons)
		// If (attacking)
			// reset cooldown	
			// call attack, 

	//if (!Is_attacking) {
	//	Attack_cooldown += dT;
	//	moveCharacter(dT);
	//	attack();
	//}
	//else {
	//	Last_texture_update += dT;

	//	// Update Current Character Frame
	//	if (Last_texture_update >= Texture_update_rate) {
	//		Attack_frame++;
	//		Last_texture_update = 0.0f;
	//	}

	//	// If attack phase complete, reset all values
	//	if (Attack_frame == attack_frames) {
	//		Attack_frame = 0;
	//		Is_attacking = false;
	//	}
	//}
}

void Demon::setIsDown(const bool b) { Is_down = b; }

void Demon::setYCoordinate() {
	switch (Frame % 4)
	{
	case (0):
		Y_coordinate -= .5f;
		break;
	case (1):
		Y_coordinate -= .5f;
		break;
	case (2):
		Y_coordinate += .5f;
		break;
	case (3):
		Y_coordinate += .5f;
		break;
	}
}

void Demon::moveCharacter(const float dT) {
	if (Is_down) {
		float height_change = dT * Height * Scale;
		Y_coordinate += height_change;
		elevation_change += height_change;
		if (Is_first_down) {
			Left_Right *= -1;
			Is_first_down = false;
		}
		else if (elevation_change >= Height * Scale / 2) {
			elevation_change = 0;
			Is_down = false;
			Is_first_down = true;
		}
	}
	else {
		X_coordinate += Speed * Left_Right * dT;
		//setYCoordinate();
	}

}

void Demon::setTexturePosition() {
	// Set Texture Position
	Texture_position.x = Width * (Frame % 4);
	Texture_position.y = 0;
}