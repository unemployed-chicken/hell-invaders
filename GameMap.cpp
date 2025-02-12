#include "GameMap.h"

GameMap::GameMap(map<string, Texture2D> textures)
	: Background(textures["background"]), Midground(textures["midground"]), Foreground(textures["foreground"]) { }

// per Chatgpt this is only necessary if we need to manage the individual pionter because std::vector manages this for us
//GameMap::~GameMap() {
//    for (Projectile* projectile : Active_projectiles) { // No longer using vector Active_projectiles
//        delete projectile;
//    }
//    Active_projectiles.clear(); // No longer using vector Active_projectiles
//}


void GameMap::appendProjectile(Mage& mage) {
	mage.setIsProjectileReady(false);
	Mage_projectiles.insertAtEnd(make_shared<Node<Projectile>>(
		Projectile( mage.getProjectileTexture(), 4, 3, mage.getXCoordinate(), mage.getYCoordinate(),
			mage.getAttackDirection(), mage_projectile_collision_offset_x, mage_projectile_collision_offset_y, 
			mage_projectile_collision_scale_x, mage_projectile_collision_scale_y, mage_projectile_rotation, true
		)
	));
}


void GameMap::appendProjectile(Demon& demon) {
	if (demon.isProjectileReady()) {
		Demon_projectiles.insertAtEnd(
			make_shared<Node<Projectile>>(
				Projectile(
					demon.getProjectileTexture(), fire_projectile_count_x, fire_projectile_count_y, demon.getXCoordinate(), demon.getYCoordinate() + demon.getHeight(),
					demon_attack_direction, fire_white_space_pixels_x, fire_white_space_pixels_y, fire_projectile_scale, 
					fire_projectile_scale, fire_projectile_rotation, false
				)
			)
		);
	}
}



void GameMap::tick(const float dT, Mage &mage){
	drawBackground();

	// Move
	moveAllDemons(dT);

	// Generate Mage Projectiles
	if (mage.getIsProjectileReady()) { appendProjectile(mage); }

	// Move and Render Mage Projectiles, Check for collisions with demons
	if (Mage_projectiles.getCount() > 0) { moveMageProjectiles(dT);	}

	// Check all Demons for collisions, Render, and Generate Projectiles
	allDemonCollisionCheckAndAppendDemonProjectiles();

	// Move and Render Demon Projectiles, Check for collisions with Mage and Mage Projectiles
	if (Demon_projectiles.getCount() > 0) { moveDemonProjectiles(dT, mage); }
}

void GameMap::drawBackground() {
	DrawTextureEx(Background, background_pos, 0.0, background_scale, WHITE);
	DrawTextureEx(Midground, midground_pos, 0.0, midground_scale, WHITE);
	DrawTextureEx(Foreground, foreground_pos, 0.0, foreground_scale, WHITE);
}

void GameMap::generateDemonsList(map<string, Texture2D> textures) {
	int x_pos{ 5 };
	for (int i = 0; i < 8; ++i) {
		DoubleLinkedList<Demon> row{};
		int y_pos{ 25 };
		for (int j = 0; j < 6; ++j) {
			if (j < 2) {
				row.insertAtEnd(make_shared<Node<Demon>>(Demon(textures["skull"], textures["fire"], x_pos, y_pos, 4)));
			}
			else if (j < 4) {
				row.insertAtEnd(make_shared<Node<Demon>>(Demon(textures["fledge"], textures["fire"], x_pos, y_pos, 4)));
			}
			else {
				row.insertAtEnd(make_shared<Node<Demon>>(Demon(textures["scamp"], textures["fire"], x_pos, y_pos, 4)));
			}

			y_pos += 50;
		}

		Demons_columns.insertAtEnd(std::make_shared<Node<DoubleLinkedList<Demon>>>(row));
		x_pos += (textures["skull"].width / 4) * character_scale;
	}
}

void GameMap::allDemonCollisionCheckAndAppendDemonProjectiles() {
	shared_ptr<Node<DoubleLinkedList<Demon>>> current_column = Demons_columns.getHead();
	while (current_column) {
		demonColumnCollisionCheck(current_column);
		
		if (current_column->Data.getCount() <= 0) {
			Demons_columns.popNode(current_column);
			current_column = current_column->Next;
		}
		else {
			// Append Projectile to Demon Projectiles if projectile is ready
			appendProjectile(current_column->Data.getTail()->Data);
			current_column = current_column->Next;
		}
	}
}

void GameMap::demonColumnCollisionCheck(shared_ptr<Node<DoubleLinkedList<Demon>>> column) {
	shared_ptr<Node<Demon>> current_demon = column->Data.getHead();
	while (current_demon) {
		if (hasCollision(current_demon->Data)) {
			column->Data.popNode(current_demon);
			current_demon = current_demon->Next;
		}
		else {
			current_demon->Data.render();
			current_demon = current_demon->Next;
		}
	}
}

bool GameMap::hasCollision(Mage& mage) {
	shared_ptr<Node<Projectile>> current_projectile = Demon_projectiles.getHead();
	while (current_projectile) {
		if (CheckCollisionRecs(current_projectile->Data.getCollisionRectangle(), mage.getCollisionRectangle())) {
			Demon_projectiles.popNode(current_projectile);
			return true;
		}
		current_projectile = current_projectile->Next;
	}
	return false;
}

bool GameMap::hasCollision(Demon& demon) {
	shared_ptr<Node<Projectile>> current_projectile = Mage_projectiles.getHead();
	while (current_projectile) {
		if (CheckCollisionRecs(current_projectile->Data.getCollisionRectangle(), demon.getCollisionRectangle())) {
			Mage_projectiles.popNode(current_projectile);
			return true;
		}
		current_projectile = current_projectile->Next;
	}
	return false;
}

void GameMap::moveMageProjectiles(const float dT) {
	shared_ptr<Node<Projectile>> current_node = Mage_projectiles.getHead();
	while (current_node) {
		if (current_node->Data.getIsActive()) {
			current_node->Data.tick(dT);

			if (current_node->Data.getYCoordinate() <= 0.0f || current_node->Data.getYCoordinate() >= window_dimensions[1]) {
				current_node->Data.setIsActive(false);
			}
			current_node = current_node->Next; 
		}
		else {
			Mage_projectiles.popNode(current_node);
			current_node = current_node->Next;
		}
	}
}

void GameMap::moveDemonProjectiles(const float dT, Mage& mage) {
	shared_ptr<Node<Projectile>> current_node = Demon_projectiles.getHead();
	while (current_node) {
		if (current_node->Data.getIsActive()) {
			current_node->Data.tick(dT);

			if (current_node->Data.getYCoordinate() <= 0.0f || 
				current_node->Data.getYCoordinate() >= window_dimensions[1] ||
				CheckCollisionRecs(current_node->Data.getCollisionRectangle(), mage.getCollisionRectangle()) ) 
			{
				current_node->Data.setIsActive(false);
			}
			current_node = current_node->Next;
		}
		else {
			Demon_projectiles.popNode(current_node);
			current_node = current_node->Next;
		}
	}
}

void GameMap::moveAllDemons(const float dT) {
	shared_ptr<Node<DoubleLinkedList<Demon>>> current_column = Demons_columns.getHead();
	bool is_first_down{ false };
	while (current_column) {
		if (current_column == Demons_columns.getHead()) {
			if (Demons_columns.getHead()->Data.getHead()->Data.calculateXCoordinate(dT) < demons_x_range[0]) {
				is_first_down = true;
			}
			// getTail() grabs the last column, the getHead() gets the first demon in the column. Could grab any demon here 
			else if (Demons_columns.getTail()->Data.getHead()->Data.calculateXCoordinate(dT) > demons_x_range[1]) {
				is_first_down = true;
			}
		}

		moveDemonColumn(current_column, dT, is_first_down);
		current_column = current_column->Next;
	}

}

void GameMap::moveDemonColumn(shared_ptr<Node<DoubleLinkedList<Demon>>> column, const float dT, const bool is_first_down) {
	shared_ptr<Node<Demon>> current_demon = column->Data.getHead();
	while (current_demon) {
		current_demon->Data.setIsFirstDown(is_first_down);
		current_demon->Data.tick(dT);
		current_demon = current_demon->Next;
	}
}



