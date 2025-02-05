#include "Projectile.h"

/* 
    Refactor Opportunity: Options are either Fire or Magic, I shouldn't need to provide all this data
	Clean this up by removing direction, collision_rec_offsets, collision_rec_scales, and rotation
*/
Projectile::Projectile(
	Texture2D texture, int number_of_objects_in_x, int number_of_objects_in_y, float x_pos, float y_pos, 
	int direction, float collision_rec_offset_x, float collision_rec_offset_y, float collision_rec_scale_x,
	float collision_rec_scale_y, float rotation, bool isMagic
) {
	Active_texture = texture;
	X_coordinate = x_pos;
	Y_coordinate = y_pos;
	isMagic ? Velocity = magic_projectile_speed * direction : Velocity = magic_projectile_speed * direction;
	Number_of_objects_in_x = number_of_objects_in_x;
	Number_of_objects_in_y = number_of_objects_in_y;
	Rotation = rotation;
	Collision_rec_white_space_offset_x = collision_rec_offset_x;
	Collision_rec_white_space_offset_y = collision_rec_offset_y;
	Collision_rec_scale_x = collision_rec_scale_x;
	Collision_rec_scale_y = collision_rec_scale_y;
	Is_magic = isMagic;

	Width = texture.width / number_of_objects_in_x - 5;
	Height = texture.height / number_of_objects_in_y;
}

Projectile::~Projectile() {
	if (debugging) { std::cout << "destroyting projectile\n"; }
}

void Projectile::setIsActive(bool boolean) { Is_active = boolean; }
bool Projectile::getIsActive() { return Is_active; }
float Projectile::getYCoordinate() { return Y_coordinate; }
void Projectile::setIsActiveToFalse() { Is_active = false; };
void Projectile::setRotation(float rotation) { Rotation = rotation; }

void Projectile::tick(const float dT) {
	Last_texture_update += dT;
	// Update Frame
	if (Last_texture_update >= Texture_update_rate ) { 
		++frame; 
		Last_texture_update = 0;
	}

	if (frame == 4) { frame = 0; }
	
	// Update Map Position
	Y_coordinate += Velocity * dT;

	// Render
	render();
}

void Projectile::render() {
	setTexturePosition();
	Rectangle source{ Texture_position.x, Texture_position.y, Width, Height };
	Rectangle destination{ X_coordinate , Y_coordinate, Scale * Width, Scale * Height };

	Vector2 origin{0, 0};

	// Temporary for now:
	Rectangle collision_rectangle = getCollisionRectangle();

	DrawTexturePro(Active_texture, source, destination, origin, Rotation, WHITE);
	if (debugging) {
		DrawRectangleLines(collision_rectangle.x, collision_rectangle.y, collision_rectangle.width, collision_rectangle.height, RED);
	};
	if (Is_magic) { setXCoordinate(); }
}

void Projectile::setTexturePosition() {
	// Set Texture Position
	Texture_position.x = 4.f;
	frame % 2 == 0 ? Texture_position.x = 4.f : Texture_position.x = Width + 5.f;
	Texture_position.y = Height;
}

Rectangle Projectile::getCollisionRectangle() {
	return Rectangle{
		X_coordinate + Collision_rec_white_space_offset_x,
		Y_coordinate + Collision_rec_white_space_offset_y,
		Width * Collision_rec_scale_x,
		Height * Collision_rec_scale_y
	};
}

void Projectile::setXCoordinate() {
	switch (frame)
	{
	case (0):
		X_coordinate += 2.5f;
	case (1): 
		X_coordinate -= 2.5f;
	case (2):
		X_coordinate -= 2.5f;
	case (3):
		X_coordinate += 2.5f;

	default:
		break;
	}
}
