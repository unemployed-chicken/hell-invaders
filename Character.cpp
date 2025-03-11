#include "Character.h"

Character::Character(
		Texture2D character_texture, Texture2D projectile_texture,
		float pos_x, float pos_y, float speed, float attack_rate, 
		int attack_direction, float texture_update_rate
) {
	Active_texture = character_texture;
	Projectile_texture = projectile_texture;
	X_coordinate = pos_x;
	Y_coordinate = pos_y;
	Speed = speed;
	Attack_rate = attack_rate;
	Attack_direction = attack_direction;
	Texture_update_rate = texture_update_rate;

}

void Character::moveCharacter(const float dT){}
Texture2D Character::getProjectileTexture() { return Projectile_texture; }
Texture2D Character::getActiveTexture() { return Active_texture; }
float Character::getXCoordinate() { return X_coordinate; }
float Character::getYCoordinate() { return Y_coordinate; }
int Character::getAttackDirection(){ return Attack_direction; }

Rectangle Character::getCollisionRectangle() { 
	return Rectangle{
		X_coordinate,
		Y_coordinate,
		Width * demon_collision_whitespace_offset,
		Height * demon_collision_whitespace_offset
	}; 
}


void Character::render() {
    Rectangle source{ Texture_position.x, Texture_position.y, Width, Height };
    Rectangle destination{ X_coordinate, Y_coordinate, Scale * Width, Scale * Height };
	Vector2 origin{ Width * demon_origin_whitespace_offset_x, Width * demon_origin_whitespace_offset_y };

	Rectangle collision_rectangle = getCollisionRectangle();
    DrawTexturePro(Active_texture, source, destination, origin, 0.0f, WHITE);
	if (debugging) {
		DrawRectangleLines(collision_rectangle.x, collision_rectangle.y, collision_rectangle.width, collision_rectangle.height, RED);
	};
}

void Character::setTexturePosition(){}
bool Character::getIsProjectileReady() { return Is_projectile_ready; }
void Character::setIsProjectileReady(const bool b) { Is_projectile_ready = b; }
float Character::getSpeed() { return Speed; }
float Character::getLeftRight() { return Left_Right; }
float Character::getWidth() { return Width; }
float Character::getHeight() { return Height; }
void Character::setSpeed(const float speed) { Speed = speed; }
void Character::setTextureUpdateRate(float update_rate) { Texture_update_rate = update_rate; }
void Character::setLeftRight(int left_right) { Left_Right = left_right; }
void Character::tick(const float dT){}
