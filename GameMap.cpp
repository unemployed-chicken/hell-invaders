#include "GameMap.h"

GameMap::GameMap(map<string, Texture2D> textures)
	: Background(textures["background"]), Midground(textures["midground"]), Foreground(textures["foreground"]), 
	  mage(textures["mage"], textures["magic"]), Regular_shield(textures["full_shield"]), Revive_shield(textures["revive_shield"]) 
{ }

bool GameMap::hasDemons() { return Demons_columns.getCount() > 0; }
bool GameMap::hasInvaded() { return has_invaded; }
bool GameMap::getHasSpecialDemonInvaded() {	return has_special_demon_spawned; }
Mage& GameMap::getMage() { return mage; }
void GameMap::setHasSpecialDemonInvaded(bool b) { has_special_demon_spawned = false; }
int GameMap::getDemonsMovedDownCount() { return demons_moved_down_count; }

void GameMap::appendProjectile() {
	mage.setIsProjectileReady(false);
	float x_coor{};
	mage.getLeftRight() == 1 ? x_coor = mage.getXCoordinate() : x_coor = mage.getXCoordinate() - mage.getWidth();

	shared_ptr<Projectile> projectile = make_shared<Projectile>(Projectile(mage.getProjectileTexture(), 4, 3, x_coor, mage.getYCoordinate(), mage.getAttackDirection(),
		mage_projectile_collision_offset_x, mage_projectile_collision_offset_y, mage_projectile_collision_scale_x,
		mage_projectile_collision_scale_y, mage_projectile_rotation, true));
	
	Mage_projectiles.insertAtEnd(make_shared<Node<Projectile>>(projectile));
}


void GameMap::appendProjectile(shared_ptr<Demon> demon) {
	if (demon->isProjectileReady()) {
		shared_ptr<Projectile> projectile = make_shared<Projectile>(demon->getProjectileTexture(), fire_projectile_count_x, fire_projectile_count_y, demon->getXCoordinate(), demon->getYCoordinate() + demon->getHeight(),
			demon_attack_direction, fire_white_space_pixels_x, fire_white_space_pixels_y, fire_projectile_scale,
			fire_projectile_scale, fire_projectile_rotation, false
		);

		Demon_projectiles.insertAtEnd( make_shared<Node<Projectile>>(projectile) );
	}
}

void GameMap::tick(const float dT){
	// Move Character // Always First
	mage.tick(dT);
	
	// Draw Background and Supplemental Data
	drawBackground();

	// Move All Demons
	moveAllDemons(dT);

	// Generate Mage Projectiles
	if (mage.getIsProjectileReady()) { appendProjectile(); }

	// Generate Regular Shields or Move Revive Shield
	generateOrMoveAllShields(dT);

	// Move and Render Mage Projectiles, Check for collisions with demons
	if (Mage_projectiles.getCount() > 0) { moveMageProjectiles(dT);	}

	// Check all Demons for collisions, Render, and Generate Projectiles
	allDemonCollisionCheckAndAppendDemonProjectiles();

	// Render Special Demon
	if (Special_demon) { Special_demon->render(); }

	// Move and Render Demon Projectiles, Check for collisions with Mage and Mage Projectiles
	if (Demon_projectiles.getCount() > 0) { moveDemonProjectiles(dT, mage); }

	// Render Shields
	if (Shields.getCount() > 0) { drawAllShields(); }

	// Draw Mage // Always Last
	mage.render();
}

void GameMap::drawBackground() {
	DrawTextureEx(Background, background_pos, 0.0, background_scale, WHITE);
	DrawTextureEx(Midground, midground_pos, 0.0, midground_scale, WHITE);
	DrawTextureEx(Foreground, foreground_pos, 0.0, foreground_scale, WHITE);

	string level_display{ "Level: " };
	level_display.append(to_string(level));

	string score_display{ "Score: " };
	score_display.append(to_string(mage.getScore()));

	DrawText(level_display.c_str(), 550, 10, 15, WHITE);
	DrawText(score_display.c_str(), 300, 10, 15, WHITE);
	drawLives();
	drawShieldCount();
}

void GameMap::drawShieldCount() {
	float starting_x{ 115 };

	for (int i = 0; i < mage.getShieldCount(); ++i) {
		DrawTexturePro(
			Regular_shield,
			Rectangle{ 0, 0, static_cast<float>(Regular_shield.width), static_cast<float>(Regular_shield.height) },
			Rectangle{ starting_x + Regular_shield.width * i, 20, static_cast<float>(Regular_shield.width), static_cast<float>(Regular_shield.height) },
			Vector2{ 0,0 },
			0.0f, 
			WHITE
		);
	}
}

void GameMap::drawLives() {
	float starting_x{ -10 };

	for (int i = 0; i < mage.getLives(); ++i) {
		Texture2D texture = mage.getActiveTexture();
		DrawTexturePro(
			texture,
			Rectangle{ 0, 0, mage.getWidth(), mage.getHeight()},
			Rectangle{ starting_x + mage.getWidth() * i, -20, mage.getWidth() * 2, mage.getHeight() * 2 },
			Vector2{ 0,0 },
			0.0f,
			WHITE
		);
	}
}

void GameMap::drawInstructions() {
	string move_instructions{ "Move left and right with 'A' and 'D' or LEFT and RIGHT arrows." };
	string attack_instructions{ "Attack with 'Space Bar', 'W', or the UP Arrow." };
	string shield_instructions{ "Cast shield with 'LEFT SHIFT', 'S', or the DOWN Arrow." };
	string end_instructions{ "Press 'ENTER' when you are ready to begin!" };
	
	DrawText(move_instructions.c_str(), 5, 50, 19, WHITE);
	DrawText(attack_instructions.c_str(), 5, 100, 20, WHITE);
	DrawText(shield_instructions.c_str(), 5, 150, 20, WHITE);
	DrawText(end_instructions.c_str(), 5, 200, 20, WHITE);
}

void GameMap::displayHomeMenu() {
	/*
	* TODO: Create home screen: 
	* Play music on home screen
	* random demons run around randomly
	* user has option for start, game properties, exit
	* If start, set intro to true and display to false
	* If properties, open up properties menu and have user adjust as they would like
	*/
}

void GameMap::generateDemonsList(map<string, Texture2D> textures) {
	level++;
	demons_moved_down_count = 0;
	has_special_demon_spawned = false;

	int x_pos{ 5 };
	for (int i = 0; i < number_of_demon_columns; ++i) {
		DoubleLinkedList<Demon> row{};
		int y_pos{ 25 };
		double demon_speed{ demon_base_speed + demon_base_speed * .25 * (level -1) };
		for (int j = 0; j < 6; ++j) {
			shared_ptr<Demon> demon;
			if (j < 2) {
				demon = make_shared<Demon>(Demon(textures["skull"], textures["fire"], x_pos, y_pos, number_of_demon_textures, skull_points * level, demon_speed));
			}
			else if (j < 4) {
				demon = make_shared<Demon>(Demon(textures["fledge"], textures["fire"], x_pos, y_pos, number_of_demon_textures, fledge_points * level, demon_speed));
			}
			else {
				demon = make_shared<Demon>(Demon(textures["scamp"], textures["fire"], x_pos, y_pos, number_of_demon_textures, scamp_points * level, demon_speed));
			}
			row.insertAtEnd(make_shared<Node<Demon>>(demon));
			y_pos += 50;
		}

		Demons_columns.insertAtEnd(make_shared<Node<DoubleLinkedList<Demon>>>(make_shared<DoubleLinkedList<Demon>>(row)));
		x_pos += (textures["skull"].width / 4) * character_scale;
	}
}

void GameMap::generateShields() {
	mage.decrementShieldCount();
	mage.setIsShieldReady(false);
	Shields.deleteAllNodes();
	for (int i = 0; i < 3; ++i) {
		shared_ptr<Shield> shield = make_shared<Shield>(Shield(Regular_shield, shield_starting_x_coordinate + shield_spacing * i));
		Shields.insertAtEnd(make_shared<Node<Shield>>(shield));
	}
}

void GameMap::drawEndGame() {
	drawBackground();
	DrawText("GAME OVER", window_dimensions[0] * end_game_coordinates_offset[0], window_dimensions[1] * end_game_coordinates_offset[1], end_game_text_size, RED);
}


void GameMap::allDemonCollisionCheckAndAppendDemonProjectiles() {
	shared_ptr<Node<DoubleLinkedList<Demon>>> current_column = Demons_columns.getHead();
	while (current_column) {
		demonColumnCollisionCheck(current_column);
		
		if (current_column->Data->getCount() <= 0) {
			Demons_columns.popNode(current_column);
		}
		else {
			// Append Projectile to Demon Projectiles if projectile is ready
			appendProjectile(current_column->Data->getTail()->Data);
		}

		current_column = current_column->Next;
	}
}

void GameMap::demonColumnCollisionCheck(shared_ptr<Node<DoubleLinkedList<Demon>>> column) {
	shared_ptr<Node<Demon>> current_demon = column->Data->getHead();
	while (current_demon) {
		if (hasCollision(current_demon->Data)) {
			mage.addScore(current_demon->Data->getPoints());
			column->Data->popNode(current_demon);
		}
		else {
			current_demon->Data->render();
		}
		
		current_demon = current_demon->Next;
	}
}

void GameMap::checkDemonProjectileForMageProjectilesCollision(shared_ptr<Node<Projectile>> demon_projectiles) {
	shared_ptr<Node<Projectile>> current_mage_projectile = Mage_projectiles.getHead();
	while (current_mage_projectile) {
		if (CheckCollisionRecs(current_mage_projectile->Data->getCollisionRectangle(), demon_projectiles->Data->getCollisionRectangle())) {
			demon_projectiles->Data->setIsActive(false);
			current_mage_projectile->Data->setIsActive(false);
			return;
		}
		current_mage_projectile = current_mage_projectile->Next;
	}
}

void GameMap::checkDemonProjectilForShieldCollision(shared_ptr<Node<Projectile>> demon_projectiles) {
	shared_ptr<Node<Shield>> current_shield = Shields.getHead();
	if (demon_projectiles->Data->getIsActive()) {
		while (current_shield) {
			if (CheckCollisionRecs(demon_projectiles->Data->getCollisionRectangle(), current_shield->Data->getCollisionRectangle())) {
				demon_projectiles->Data->setIsActive(false);
				if (!current_shield->Data->getIsPersistent()) { current_shield->Data->takeDamage(); }
				return;
			}

			current_shield = current_shield->Next;
		}
	}

}

void GameMap::drawAllShields() {
	shared_ptr<Node<Shield>> current_shield = Shields.getHead();
	while (current_shield) {
		if (current_shield->Data->getIsActive()) {
			current_shield->Data->render();
		}
		else {
			Shields.popNode(current_shield);
		}

		current_shield = current_shield->Next;
	}
}

void GameMap::mageTakesDamage() {
	mage.setIsCastingShield(false);
	mage.setIsShieldReady(false);
	mage.takeDamage();
	Shields.deleteAllNodes();

}

void GameMap::generateOrMoveAllShields(const float dT) {
	if (mage.getIsShieldReady() && mage.getShieldCount() > 0) {
		generateShields(); 
	}
	else if (mage.getIsPostReviveActive()) {
		if (mage.getIsReviveShieldActive()) {
			moveReviveShield(dT);
		}
		else if (!mage.getIsReviveShieldActive() && mage.getTextureFrame() == 0) {

			generateReviveShield();
		}
	}
}

void GameMap::moveReviveShield(const float dT) {
	// Revive Shield should be only shield at this point. 
	Shields.getHead()->Data->tick(dT);
	if (!Shields.getHead()->Data->getIsActive()) {
		mage.setIsReviveShieldActive(false);
	}
}

void GameMap::destroySpecialDemon(const bool is_killed) {
	Special_demon = nullptr;
	
	if (is_killed) {
		mage.incrementShieldCount();
	}
}


void GameMap::generateReviveShield() {
	shared_ptr<Shield> shield = make_shared<Shield>(ReviveShield(Revive_shield));
	Shields.insertAtEnd(make_shared<Node<Shield>>(shield));
}

bool GameMap::hasCollision(shared_ptr<Demon> demon) {
	if (CheckCollisionRecs(mage.getCollisionRectangle(), demon->getCollisionRectangle())) {
		has_invaded = true;
		return false;
	}

	shared_ptr<Node<Projectile>> current_projectile = Mage_projectiles.getHead();
	while (current_projectile) {
		if (CheckCollisionRecs(current_projectile->Data->getCollisionRectangle(), demon->getCollisionRectangle())) {
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
		if (current_node->Data->getIsActive()) {
			current_node->Data->tick(dT);

			if (current_node->Data->getYCoordinate() <= 0.0f || current_node->Data->getYCoordinate() >= window_dimensions[1]) {
				current_node->Data->setIsActive(false);
			} 
			else if (Special_demon && CheckCollisionRecs(current_node->Data->getCollisionRectangle(), Special_demon->getCollisionRectangle())) {
				current_node->Data->setIsActive(false);
				destroySpecialDemon(true);
			}
		}
		else {
			Mage_projectiles.popNode(current_node);
		}
		current_node = current_node->Next;
	}
}

void GameMap::moveDemonProjectiles(const float dT, Mage& mage) {
	shared_ptr<Node<Projectile>> current_node = Demon_projectiles.getHead();
	bool is_mage_invulnerable{ mage.getIsPostReviveActive() || mage.getIsHurt() };
	while (current_node) {
		if (current_node->Data->getIsActive()) {
			current_node->Data->tick(dT);

			if (current_node->Data->getYCoordinate() <= 0.0f || current_node->Data->getYCoordinate() >= window_dimensions[1]) {
				current_node->Data->setIsActive(false);
			} 
			else if (!is_mage_invulnerable && CheckCollisionRecs(current_node->Data->getCollisionRectangle(), mage.getCollisionRectangle())) {
				current_node->Data->setIsActive(false);
				mageTakesDamage();
			}
			else {
				checkDemonProjectileForMageProjectilesCollision(current_node);
				checkDemonProjectilForShieldCollision(current_node);
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
	if (Special_demon) { Special_demon->moveCharacter(dT); }

	shared_ptr<Node<DoubleLinkedList<Demon>>> current_column = Demons_columns.getHead();
	bool is_first_down{ false };
	bool is_speed_bump_row = false;

	while (current_column) {
		if (current_column == Demons_columns.getHead()) {
			if (Demons_columns.getHead()->Data->getHead()->Data->calculateXCoordinate(dT) < demons_x_range[0] ||
				Demons_columns.getTail()->Data->getHead()->Data->calculateXCoordinate(dT) > demons_x_range[1] ) 
			{
				is_first_down = true;
				++demons_moved_down_count;
				if (demons_moved_down_count % (number_of_rows_moved_per_speed_boost) == 0) {
					is_speed_bump_row = true;
				}
				
			}
		}

		moveDemonColumn(current_column, dT, is_first_down, is_speed_bump_row);
		current_column = current_column->Next;
	}
}

void GameMap::moveDemonColumn(shared_ptr<Node<DoubleLinkedList<Demon>>> column, const float dT, const bool is_first_down, const bool is_speed_bump) {
	shared_ptr<Node<Demon>> current_demon = column->Data->getHead();
	while (current_demon) {
		if (is_speed_bump) { current_demon->Data->setSpeed(current_demon->Data->getSpeed() + speed_increase); }
		current_demon->Data->setIsFirstDown(is_first_down);
		current_demon->Data->tick(dT);
		current_demon = current_demon->Next;
	}
}


void GameMap::generateSpecialDemon(map<string, Texture2D> textures) {
	has_special_demon_spawned = true;
	float x_coordinate{};
	int left_right{ 1 };
	if (level % 2 == 1) {
		x_coordinate = 0;
	}
	else {
		x_coordinate = window_dimensions[0];
		left_right *= -1;
	}

	Special_demon = make_shared<Demon>(Demon(textures["eye"], textures["fire"], x_coordinate, 20, 4, 500, 75));
	Special_demon->setLeftRight(left_right);
}


