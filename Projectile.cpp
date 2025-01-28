#include "Projectile.h"

Projectile::Projectile(Texture2D texture, int number_of_objects_in_x, int number_of_objects_in_y, float x_pos, float y_pos, int direction) {
	Texture = texture;
	X_coordinate = x_pos;
	Y_coordinate = y_pos;
	Velocity = projectile_speed * direction;
	Number_of_objects_in_x = number_of_objects_in_x;
	Number_of_objects_in_y = number_of_objects_in_y;

	Width = texture.width / number_of_objects_in_x;
	Height = texture.height / number_of_objects_in_y;
}

void Projectile::tick(float dT) {
	Last_texture_update += dT;
	Y_coordinate += Velocity * dT;
	// Render here? 
}

void Projectile::render() {

}
