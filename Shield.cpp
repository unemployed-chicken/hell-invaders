#include "Shield.h"

Shield::Shield(Texture2D full_shield, float x_position): Shield_Texture(full_shield), X_coordinate(x_position) {
	Width = Shield_Texture.width;
	Height = Shield_Texture.height;
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
	Color color = getShieldColor();

	Rectangle source{ 0, 0, Width, Height };
	Rectangle destination{ X_coordinate, Y_coordinate, Width * Width_scale, Height * Height_scale };

	Rectangle collision_rectangle = getCollisionRectangle();
	Vector2 origin{ 0,0 };

	DrawTexturePro(Shield_Texture, source, destination, origin, 0.0f, color);
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


Color Shield::getShieldColor() {
	if (Damage_count < 2) {
		return WHITE;
	}
	else if (Damage_count < 4) {
		return ORANGE;
	}
	else {
		return RED;
	}
}

void Shield::tick(const float dT){
	Y_coordinate += revive_shield_movement_speed * dT;
	render();

	if (Y_coordinate <= 0) { Is_active = false; }
}
