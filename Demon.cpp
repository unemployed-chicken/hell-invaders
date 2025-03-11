#include "Demon.h"


Demon::Demon(Texture2D character_texture, Texture2D projectile_texture, Properties& properties, int demon_x_pos, int demon_y_pos, int texture_count, int points, float speed) :
	Character(character_texture, projectile_texture, demon_x_pos, demon_y_pos, speed, properties.getDemonAttackRateInSeconds(), 1, properties.getNumberOfTexureUpdatesRatePerSecond()
	) {
	Width = static_cast<float>(character_texture.width) / texture_count;
	Height = static_cast<float>(character_texture.height);
	Points = points;
}
Demon::~Demon() {
	if (debugging) { std::cout << "Destroying Demon" << '\n'; }
}

int Demon::getPoints() { return Points; }
void Demon::setIsFirstDown(const bool b) { Is_first_down = b; }
bool Demon::getIsFirstDown() { return Is_first_down; }
float Demon::calculateXCoordinate(const float dT) {
	return getXCoordinate() + (getSpeed() * getLeftRight() * dT);
}

void Demon::tick(const float dT) {
	Last_texture_update += dT;
	Attack_cooldown += dT;
	attack_pause += dT;

	if (Last_texture_update >= Texture_update_rate) {
		Frame++;
		Last_texture_update = 0.0f;
	}

	// MoveCharacter
	moveCharacter(dT);
	
	// setTexturePosition
	setTexturePosition();
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
	}

}


bool Demon::isProjectileReady() {
	if (Attack_cooldown > Attack_rate) {
		if (attack_pause > attack_retry_rate) {
			int random = rand() % 100;
			if (random < 20) {
				Attack_cooldown = 0;
				return true;
			}
			else {
				attack_pause = 0;
			}
		}
	}
	return false;
}

void Demon::setTexturePosition() {
	// Set Texture Position
	Texture_position.x = Width * (Frame % 4);
	Texture_position.y = 0;
}
