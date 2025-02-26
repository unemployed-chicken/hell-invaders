#include "Shield.h"

Shield::Shield(Texture2D full_shield, Texture2D mid_shield, Texture2D low_shield, Texture2D revive_shield, float x_position):
	Full_shield(full_shield), Mid_shield(mid_shield), Low_shield(low_shield), Revive_shield(revive_shield), X_coordinate(x_position) 
{
	Width = Full_shield.width;
	Height = Full_shield.height;
}

bool Shield::getIsActive() { return Is_active; }
bool Shield::getIsPersistent() { return Is_persistent; }
void Shield::takeDamage() {
	Damage_count++; 
	if (Damage_count == 6) {
		Is_active = false;
	}
}

void Shield::render() { 
	Texture2D texture = getActiveTexture();

	Rectangle source{ 0, 0, Width, Height };
	Rectangle destination{ X_coordinate, Y_coordinate, Width * Width_scale, Height * Height_scale };

	Rectangle collision_rectangle = getCollisionRectangle();
	Vector2 origin{ 0,0 };

	DrawTexturePro(texture, source, destination, origin, 0.0f, WHITE);
	if (debugging) {
		DrawRectangleLines(collision_rectangle.x, collision_rectangle.y, collision_rectangle.width, collision_rectangle.height, RED);
	};
}


Rectangle Shield::getCollisionRectangle() {
	return Rectangle{
		X_coordinate,
		Y_coordinate,
		Width * Width_scale,
		Height * Height_scale
	};
}


Texture2D Shield::getActiveTexture() {
	if (Damage_count < 2) {
		return Full_shield;
	}
	else if (Damage_count < 4) {
		return Mid_shield;
	}
	else {
		return Low_shield;
	}
}

void Shield::tick(const float dT){
	Y_coordinate += revive_shield_movement_speed * dT;
	render();

	if (Y_coordinate <= 0) { Is_active = false; }
}
