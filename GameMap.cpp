#include "GameMap.h"

GameMap::GameMap(map<string, Texture2D> textures)
	: Background(textures["main_background_1"]), Midground(textures["main_background_2"]), Foreground(textures["main_background_3"]), 
	  mage(textures["mage"], textures["magic"], Props), Regular_shield(textures["full_shield"]), Revive_shield(textures["revive_shield"]) 
{ }


bool GameMap::hasDemons() { return Demons_columns.getCount() > 0; }
bool GameMap::hasInvaded() { return has_invaded; }
bool GameMap::getHasSpecialDemonInvaded() {	return has_special_demon_spawned; }
bool GameMap::getIsMainScreen(){ return Is_main_screen; }
bool GameMap::getIsIntro() { return Is_intro; }
bool GameMap::getIsEndGameRequested() { return Is_end_game_requested; }
bool GameMap::getPropertiesShouldStartGameWithShieldsActive() {	return Props.getBoolPropertyValue("Should_start_with_shields_active"); }
bool GameMap::getIsPropertiesScreen() {	return Is_properties_screen; }
Mage& GameMap::getMage() { return mage; }
void GameMap::setHasSpecialDemonInvaded(const bool b) { has_special_demon_spawned = false; }
int GameMap::getDemonsMovedDownCount() { return demons_moved_down_count; }
void GameMap::resetProperties() { Props = Properties(); }
void GameMap::setResetShieldCountToStartingAmount() { mage.setShieldCountToStartingAmount(Props.getIntPropertyValue("Number_of_starting_shields")); }
void GameMap::clearAllShields() { Shields.deleteAllNodes(); }

void GameMap::updatePropertySelectorCoordinate(int x) {
	Property_selector_coordinate += x;
	if (Visible_properties.getCount() == 5) {
		if (x > 0) { Visible_properties.deleteHead(false); }
		else { Visible_properties.deleteTail(false); }
	}

	if (x > 0) {
		if (Visible_properties.getTail()->Next) {
			shared_ptr<Node<Property>> next_property_node = Props.getPropertyByName(Visible_properties.getTail()->Next->Data->getKey());
			if (next_property_node) { Visible_properties.insertAtEnd(next_property_node); }
		}
	}
	else {
		if (Visible_properties.getHead()->Previous) {
			shared_ptr<Node<Property>> previous_property_node = Props.getPropertyByName(Visible_properties.getHead()->Previous->Data->getKey());
			if (previous_property_node) { Visible_properties.insertAtFront(previous_property_node); }
		}
	}

}

void GameMap::populateVisibleProperties() {
	int i = Property_selector_coordinate - 2;
	while (true) {
		if (i > 0) {
			//shared_ptr<Node<Property>> first_property_node = Props.getPropertyByPosition(i);
			Visible_properties.insertAtEnd(Props.getPropertyByPosition(i));
			break;
		}

		if (i > Property_selector_coordinate + 2) { cout << "populateVisibleProperties did not find a property at position " << i << ". Stuck in infinite loop.\n"; }
		
		i++;
	}

	for (i; i < Property_selector_coordinate + 2; i++) {
		if (i <= Props.getCount()) {
			//shared_ptr<Node<Property>> next_property_node = Props.getPropertyByName(Visible_properties.getTail()->Next->Data->getKey());
			Visible_properties.insertAtEnd(Props.getPropertyByName(Visible_properties.getTail()->Next->Data->getKey()));
		}
	}
}

void GameMap::appendProjectile() {
	mage.setIsProjectileReady(false);
	float x_coor{};
	mage.getLeftRight() == 1 ? x_coor = mage.getXCoordinate() : x_coor = mage.getXCoordinate() - mage.getWidth();

	shared_ptr<Projectile> projectile = make_shared<Projectile>(Projectile(mage.getProjectileTexture(), Props, 4, 3, x_coor, mage.getYCoordinate(), mage.getAttackDirection(),
		mage_projectile_collision_offset_x, mage_projectile_collision_offset_y, mage_projectile_collision_scale_x,
		mage_projectile_collision_scale_y, mage_projectile_rotation, true));
	
	Mage_projectiles.insertAtEnd(make_shared<Node<Projectile>>(projectile));
}


void GameMap::appendProjectile(shared_ptr<Demon> demon) {
	if (demon->isProjectileReady()) {
		shared_ptr<Projectile> projectile = make_shared<Projectile>(demon->getProjectileTexture(), Props, fire_projectile_count_x, fire_projectile_count_y, demon->getXCoordinate(), demon->getYCoordinate() + demon->getHeight(),
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

void GameMap::drawSaveAndExitOptions() {
	string save{ "Save and Exit" }; // 13
	string restore_defaults{ "Restore Defaults" }; // 16
	string exit{ "Exit without Save" }; // 17

	DrawText(save.c_str(), 50, 600, properties_font_size, WHITE);
	DrawText(restore_defaults.c_str(), 250, 600, properties_font_size, WHITE);
	DrawText(exit.c_str(), 450, 600, properties_font_size, WHITE);
}

void GameMap::drawMainScreen(map<string, Texture2D> textures, const float dT) {
	drawMainScreenBackground();

	// Move or Generate Demons at random
	generateRandomDemon(textures); 

	if (Demons_columns.getCount() > 0) { moveAllDemons(dT, true); }
}

void GameMap::drawFloatProperty(float value, int x_position, int y_position) {
	// To Be Changed
	string string_value{ "Value: " };
	string_value.append(to_string(value));
	DrawText(string_value.c_str(), x_position, y_position, properties_font_size, WHITE);
}

void GameMap::drawBoolProperty(bool value, int x_position, int y_position) {
	// To Be Changed
	string string_value{ "Value: " };
	if (value) { string_value.append("True"); }
	else { string_value.append("False"); }
	//string_value.append(to_string(value));
	DrawText(string_value.c_str(), x_position, y_position, properties_font_size, WHITE);
}

void GameMap::drawIntProperty(int value, int x_position, int y_position) {
	// To Be Changed
	string string_value{ "Value: " };
	string_value.append(to_string(value));
	DrawText(string_value.c_str(), x_position, y_position, properties_font_size, WHITE);
}

void GameMap::checkPropertiesPageUserInput() {
	if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown)) {
		if (Property_selector_coordinate > 1) { updatePropertySelectorCoordinate(-1); }
		else { moveSelectBoxLocationToSaveProperties(); }
		Select_box_movement_cooldown = 0.f;

	}
	else if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown)) {
		if (Property_selector_coordinate < Props.getCount()) { updatePropertySelectorCoordinate(1); }
		else { moveSelectBoxLocationToSaveProperties(); }
		Select_box_movement_cooldown = 0.f;
	}
}

void GameMap::saveOrRestorDefaults() {
	if (Select_box_location.x == 50) {
		Props.saveProperties();
	}
	else if (Select_box_location.x == 250) {
		Props.restoreDefaults();
	}
	else {}
}

bool GameMap::checkPropertiesPageSaveOptionsInput() {
	bool is_selected{ false };
	
	if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown)) {
		moveSelectBoxLocationToGameProperties();
		Select_box_movement_cooldown = 0.f;
	}
	if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown)) {
		if (Select_box_location.x > 50) { 
			Select_box_location.x -= 200; 
			Select_box_movement_cooldown = 0.f;
		}
	}
	if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown)) {
		if (Select_box_location.x < 450) {
			Select_box_location.x += 200;
			Select_box_movement_cooldown = 0.f;
		}
	}
	if (IsKeyPressed(KEY_ENTER)) {
		is_selected = true;
	}

	return is_selected;
}

void GameMap::moveSelectBoxLocationToSaveProperties() {
	Select_box_location.x = 50;
	Select_box_location.y = 600;
}

void GameMap::moveSelectBoxLocationToGameProperties() {
	Select_box_location.x = 25;
	Select_box_location.y = 300;
}

void GameMap::moveSelectBoxLocationToGamePlayOptions() {
	Select_box_location.x = 165;
	Select_box_location.y = 190;
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

void GameMap::drawMainScreenBackground() {
	DrawTextureEx(Background, Vector2{-250, 0}, 0.0, 4.0, WHITE);
	DrawTextureEx(Midground, Vector2{}, 0.0, 4.0, WHITE);
	DrawTextureEx(Midground, Vector2{-200, 200}, 0.0, 4.0, WHITE);
	DrawTextureEx(Foreground, Vector2{}, 0.0, 2.5, WHITE);
	DrawTextureEx(Foreground, Vector2{300, 175}, 0.0, 4.0, WHITE);
	DrawTextureEx(Foreground, Vector2{100, 350}, 0.0, 2.0, WHITE);
}

void GameMap::drawPlayerMenuOptions() {
	string start_game{ "Start Game" };
	string game_options{ "Game Options" };
	string exit_game_display{ "Exit" };

	DrawText(start_game.c_str(), 175, 200, 50, WHITE);
	DrawText(game_options.c_str(), 175, 300, 50, WHITE);
	DrawText(exit_game_display.c_str(), 175, 400, 50, WHITE);
}

void GameMap::drawProperty(shared_ptr<Node<Property>> property) {
	int y_position = properties_starting_y_coordinate + (property->Data->getLocation() - Property_selector_coordinate) * properties_spacing;
	DrawText(property->Data->getKey().c_str(), 25, y_position, properties_font_size, WHITE);
	

	//int value_x_position = property->Data->getPropertyWidth(properties_font_size) + 15; // Spacinge is not working as expected
	int value_x_position = 450; // Spacinge is not working as expected

	// Draw property value. 
	if (property->Data->getIsFloat()) { drawFloatProperty(Props.getFloatPropertyValue(property->Data->getKey()), value_x_position, y_position); }
	else if (property->Data->getIsBool()) { drawBoolProperty(Props.getBoolPropertyValue(property->Data->getKey()), value_x_position, y_position); }
	else { drawIntProperty(Props.getIntPropertyValue(property->Data->getKey()), value_x_position, y_position); }
}

int GameMap::drawPlayerPropertyOptions() {
	int width{ 16 * properties_font_size };
	
	shared_ptr<Node<Property>> current_property = Visible_properties.getHead();
	
	while (current_property) {
		drawProperty(current_property);
		if (current_property->Data->getLocation() == Property_selector_coordinate && Select_box_location.y < 600) {
			width = current_property->Data->getPropertyWidth(properties_font_size); 
		}

		current_property = current_property->Next;
		if (current_property == Visible_properties.getTail()->Next) { break; }
	}
	
	drawSaveAndExitOptions();

	return width;
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

void GameMap::displayHomeMenu(map<string, Texture2D> textures, const float dT) {
	Select_box_movement_cooldown += dT;
	drawMainScreen(textures, dT);

	drawPlayerMenuOptions();

	// Move and Render Player Select Box
	bool has_player_selected_option = playerMainScreenTick();

	// Take action if player has selected an option
	if (has_player_selected_option && Select_box_location.y == 190) {
		Is_main_screen = false;
		updateBackgroundTextures(textures);
		Demons_columns.deleteAllNodes();
		
		if (!Props.getBoolPropertyValue("Should_skip_intro")) {
			Is_intro = true; 
		}
		else if (Props.getBoolPropertyValue("Should_skip_intro") && Props.getBoolPropertyValue("Should_start_with_shields_active")) {
			generateShields();
		}
	} 
	else if ( has_player_selected_option && Select_box_location.y == 290 ) {
		Is_main_screen = false;
		Is_properties_screen = true;
		moveSelectBoxLocationToGameProperties();
	}
	else if ( has_player_selected_option && Select_box_location.y == 390 ) {
		Is_end_game_requested = true;
	}

	/*
	* TODO: 
	* Play music on home screen
	* 
	* Provide menu navigation instructions
	*/
}

void GameMap::displayPropertiesMenu(map<string, Texture2D> textures, const float dT) {
	// TODO: ? If a user makes no changes and selects save and close, How do I revert their changes? It may already be doing that, so take a look
	// TODO: Game crashes when selecting Update Properties
	// TODO: When Moving down, the box surrounds the second property. When moving up, the box surrounds the 4th property.
	// TODO: Allow user to adjust properties
	Select_box_movement_cooldown += dT;

	if (Visible_properties.getCount() < 1) { populateVisibleProperties(); }

	drawMainScreen(textures, dT);

	// Move Player Select Box, Populate and Render Options, Render Player Select Box
	bool has_player_selected_option = playerPropertiesScreenTick();

	// Decide what actions to take
	if (has_player_selected_option && Select_box_location.y == 600) {
		saveOrRestorDefaults();

		moveSelectBoxLocationToGamePlayOptions();

		Is_properties_screen = false;
		Is_main_screen = true;
	}
}

void GameMap::setIsIntro(const bool b) { Is_intro = b; }

void GameMap::generateDemonsList(map<string, Texture2D> textures) {
	level++;
	demons_moved_down_count = 0;
	has_special_demon_spawned = false;

	int x_pos{ 5 };
	for (int i = 0; i < Props.getIntPropertyValue("Number_of_demon_columns"); ++i) {
		DoubleLinkedList<Demon> row{};
		int y_pos{ 25 };
		double demon_speed{ Props.getFloatPropertyValue("Demon_base_speed_in_pixels_per_second") + Props.getFloatPropertyValue("Demon_level_acceleration_percentage") * (level - 1)};
		int skull_points = Props.getIntPropertyValue("Demon_base_points") * Props.getIntPropertyValue("Skull_score_multiplier");
		int fledge_points = Props.getIntPropertyValue("Demon_base_points") * Props.getIntPropertyValue("Fledgling_score_multiplier");
		int scamp_points = Props.getIntPropertyValue("Demon_base_points") * Props.getIntPropertyValue("Scamp_score_multiplier");
		
		for (int j = 0; j < 6; ++j) {
			shared_ptr<Demon> demon;
			if (j < 2) {
				demon = make_shared<Demon>(Demon(textures["skull"], textures["fire"], Props, x_pos, y_pos, number_of_demon_textures, skull_points * level, demon_speed));
			}
			else if (j < 4) {
				demon = make_shared<Demon>(Demon(textures["fledge"], textures["fire"], Props, x_pos, y_pos, number_of_demon_textures, fledge_points * level, demon_speed));
			}
			else {
				demon = make_shared<Demon>(Demon(textures["scamp"], textures["fire"], Props, x_pos, y_pos, number_of_demon_textures, scamp_points * level, demon_speed));
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

void GameMap::generateRandomDemon(map<string, Texture2D> textures) {
	int random = rand();
	if (Demons_columns.getCount() < 1 && random % 2500 <= 10) {
		// Generate a new column and populate with a demon
		DoubleLinkedList<Demon> random_demons{};
		random_demons.insertAtEnd(make_shared<Node<Demon>>(generateDemonWithRandomTexture(textures, random)));
		Demons_columns.insertAtEnd(make_shared<Node<DoubleLinkedList<Demon>>>(make_shared<DoubleLinkedList<Demon>>(random_demons)));
	}
	else if (Demons_columns.getCount() > 0 && Demons_columns.getHead()->Data->getCount() < 7 && random % 2500 <= 10) {
		// Populate existing column with a demon
		shared_ptr<Demon> demon = generateDemonWithRandomTexture(textures, random);
		Demons_columns.getHead()->Data->insertAtEnd(make_shared<Node<Demon>>(generateDemonWithRandomTexture(textures, random)));
	}
}

void GameMap::updateBackgroundTextures(map<string, Texture2D> textures) {
	Background = textures["background"];
	Midground = textures["midground"];
	Foreground = textures["foreground"];
}

bool GameMap::playerMainScreenTick() {
	if ((IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown) ) {
		Select_box_location.y < 390 ? Select_box_location.y += 100 : Select_box_location.y += 0;
		Select_box_movement_cooldown = 0.f;
	} else if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) && (Select_box_movement_cooldown >= select_box_movement_minimum_cooldown)) {
		Select_box_location.y > 190 ? Select_box_location.y -= 100 : Select_box_location.y -= 0;
		Select_box_movement_cooldown = 0.f;
	}

	int width{};
	
	if (Select_box_location.y == 190) { width = 305; }
	else if (Select_box_location.y == 290) { width = 350; }
	else { width = 115; }

	DrawRectangleLines(Select_box_location.x, Select_box_location.y, width, 70, RED);

	if (IsKeyPressed(KEY_ENTER)) { return true;	}
	return false;
}

bool GameMap::playerPropertiesScreenTick() {
	// Move Options based on user input
	bool is_selected{ false };
	
	if (Select_box_location.y < 600) {
		checkPropertiesPageUserInput();
	}
	else {
		is_selected = checkPropertiesPageSaveOptionsInput();
	}

	// Draw Player Options and return width of the currently selectable option
	int width = drawPlayerPropertyOptions();

	// Draw Select Box
	DrawRectangleLines(Select_box_location.x - 5, Select_box_location.y - 5, width, properties_font_size + 10, RED);

	return is_selected;
}

shared_ptr<Demon> GameMap::generateDemonWithRandomTexture(map<string, Texture2D> textures, const int random) {
	Texture2D texture;
	float x_pos;
	float y_pos{ static_cast<float>( random % 590 )}; // y_pos is range of 0 to 589
	float speed{ 50.f + random % 100 }; // Base speed is 50 pix/sec
	float left_right{ 1 };
	
	if (random % 2 == 0) {
		x_pos = 0;
	}
	else {
		x_pos = window_dimensions[0];
		left_right *= -1;
	}

	if (random % 8 <= 1) { texture = textures["skull"];	}
	else if (random % 8 <= 3) { texture = textures["fledge"];	}
	else if (random % 8 <= 5) { texture = textures["scamp"]; }
	else { texture = textures["eye"];	}

	shared_ptr<Demon> demon = make_shared<Demon>(Demon(texture, textures["fire"], Props, x_pos, y_pos, number_of_demon_textures, 0, speed));
	demon->setLeftRight(left_right);
	return demon;
}

void GameMap::generateReviveShield() {
	shared_ptr<Shield> shield = make_shared<Shield>(ReviveShield(Revive_shield, Props));
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

void GameMap::moveAllDemons(const float dT, const bool is_main_screen) {
	if (Special_demon) { Special_demon->moveCharacter(dT); }

	shared_ptr<Node<DoubleLinkedList<Demon>>> current_column = Demons_columns.getHead();
	bool is_first_down{ false };
	bool is_speed_bump_row = false;

	while (current_column) {
		if (current_column == Demons_columns.getHead() && !is_main_screen) {
			if (Demons_columns.getHead()->Data->getHead()->Data->calculateXCoordinate(dT) < demons_x_range[0] ||
				Demons_columns.getTail()->Data->getHead()->Data->calculateXCoordinate(dT) > demons_x_range[1] ) 
			{
				is_first_down = true;
				++demons_moved_down_count;
				if (demons_moved_down_count % Props.getIntPropertyValue("Number_of_rows_before_speed_boost") == 0) {
					is_speed_bump_row = true;
				}
				
			}
		}

		moveDemonColumn(current_column, dT, is_first_down, is_speed_bump_row, is_main_screen);
		current_column = current_column->Next;
	}
}

void GameMap::moveDemonColumn(shared_ptr<Node<DoubleLinkedList<Demon>>> column, const float dT, const bool is_first_down, const bool is_speed_bump, const bool is_main_screen) {
	shared_ptr<Node<Demon>> current_demon = column->Data->getHead();
	while (current_demon) {
		if (is_speed_bump) { current_demon->Data->setSpeed(current_demon->Data->getSpeed() + Props.getFloatPropertyValue("Demon_acceleration_in_pixels_per_second")); }
		current_demon->Data->setIsFirstDown(is_first_down);
		current_demon->Data->tick(dT);

		if (is_main_screen) {
			if (current_demon->Data->getXCoordinate() <= -50.0 || current_demon->Data->getXCoordinate() > 650) { column->Data->popNode(current_demon); }
			else { current_demon->Data->render(); }
		}

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

	Special_demon = make_shared<Demon>(Demon(textures["eye"], textures["fire"], Props, x_coordinate, 20, 4, 500, 75));
	Special_demon->setLeftRight(left_right);
}


