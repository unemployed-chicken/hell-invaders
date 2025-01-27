#include "Mage.h"
#include <iostream>

constexpr float mage_speed{ 200.f };
constexpr float mage_fire_rate{ .25 };
constexpr int mage_textures_per_row{ 11 };
constexpr int mage_textures_per_column{ 9 };
constexpr Vector2 origin{ 42.5, 70 }; // This offsets the white space in the Mage Texture
constexpr float collision_rec_white_space_off_set{ 1.5f };

Mage::Mage(Texture2D texture) : Character(texture, starting_x_pos, starting_y_pos, mage_speed, mage_fire_rate) {
	Width = static_cast<float>(texture.width) / mage_textures_per_row;
	Height = static_cast<float>(texture.width) / mage_textures_per_column;
};

void Mage::moveCharacter(float dT) {
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
	}
}

void Mage::render() {
	Rectangle source{ Texture_position.x, Texture_position.y, Width * Left_Right, Height };
	Rectangle destination{ X_coordinate, Y_coordinate, Scale * Width, Scale * Height };
	
	// Temporary for now:
	Rectangle collision_rectangle = getCollisionRectangle();

	DrawTexturePro(Active_texture, source, destination, origin, 0.0f, WHITE);
	DrawRectangleLines(collision_rectangle.x, collision_rectangle.y, collision_rectangle.width, collision_rectangle.height, RED);
}

Rectangle Mage::getCollisionRectangle(){
	return Rectangle{ 
		X_coordinate,	
		Y_coordinate, 
		Width * collision_rec_white_space_off_set, 
		Height * collision_rec_white_space_off_set 
	};
}


