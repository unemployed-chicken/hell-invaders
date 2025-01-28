#include "Character.h"

Character::Character(Texture2D character_texture, Texture2D projectile_texture, float pos_x, float pos_y, float speed, float attack_rate) {
	Active_texture = character_texture;
	Projectile_texture = projectile_texture;
	X_coordinate = pos_x;
	Y_coordinate = pos_y;
	Speed = speed;
	Attack_rate = attack_rate;
}

void Character::moveCharacter(float dT){}

void Character::render() {
    Rectangle source{ Texture_position.x, Texture_position.y, Width, Height };
    Rectangle destination{ X_coordinate, Y_coordinate, Scale * Width, Scale * Height };
	Vector2 origin{ 0, 0 };
    DrawTexturePro(Active_texture, source, destination, origin, 0.0f, WHITE);
	DrawRectangleLines(X_coordinate, Y_coordinate, Width*1.5, Height*1.5, RED);
}

Rectangle Character::getCollisionRectangle() {return Rectangle{};}
void Character::attack(){}
void Character::tick(float dT){}
