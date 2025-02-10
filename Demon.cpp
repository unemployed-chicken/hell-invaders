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
	Attack_cooldown += dT;

	if (Last_texture_update >= Texture_update_rate) {
		Frame++;
		Last_texture_update = 0.0f;
	}

	calculateIsProjectileReady();

	// MoveCharacter
	moveCharacter(dT);
	
	// setTexturePosition
	setTexturePosition();

	// No longer rendering during tick. Instead rendering during collision check
	// Render Character
	//render();
}

void Demon::setIsFirstDown(const bool b) { Is_first_down = b; }

float Demon::calculateXCoordinate(const float dT) {
	return getXCoordinate() + (getSpeed() * getLeftRight() * dT);
}

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
	if (Is_first_down) {
		Left_Right *= -1;
		Is_first_down = false;
		Is_down = true;
	}
	if (Is_down) {
		float height_change = dT * Height * Scale;
		Y_coordinate += height_change;
		elevation_change += height_change;

		if (elevation_change >= Height * Scale / 2) {
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

void Demon::calculateIsProjectileReady() {
	if (Attack_cooldown > Attack_rate) {
		if (rand() % 100 > 75) {
			Is_projectile_ready = true;
			Attack_cooldown = 0;
		}
	}
}

void Demon::setTexturePosition() {
	// Set Texture Position
	Texture_position.x = Width * (Frame % 4);
	Texture_position.y = 0;
}