#pragma once

#include "Demon.h"
#include "DoubleLinkedList.h"
#include "Mage.h"
#include "MusicController.h"
#include "Projectile.h"
#include "Properties.h"
#include "raylib.h"
#include "ReviveShield.h"
#include "Shield.h"
#include <iostream>
#include <string>
#include <memory>
#include <map>
using std::cout;
using std::map;
using std::pair;
using std::shared_ptr;
using std::string;
using std::make_shared;
using std::to_string;

extern const float window_dimensions[2];
extern const bool debugging;

// Backgrounds Properties
const float background_scale{ 3.0f };
const float midground_scale{ 3.0f };
const float foreground_scale{ 1.1f };

const Vector2 background_pos{ -25.0f, 0.0f };
const Vector2 midground_pos{ 0.0f, -50.0f };
const Vector2 foreground_pos{ -30.0f, 390 };

constexpr float mage_projectile_collision_offset_x{ 24.0 };
constexpr float mage_projectile_collision_offset_y{ -31.0 };
constexpr float mage_projectile_collision_scale_x{ 1.5 };
constexpr float mage_projectile_collision_scale_y{ 2.0 };
constexpr float mage_projectile_rotation{ -90.0 };
constexpr float end_game_coordinates_offset[2]{.15, .35};
constexpr float end_game_text_size{ 75 };
constexpr float shield_starting_x_coordinate{ 50 };
constexpr float shield_spacing{ 225 };
constexpr int number_of_demon_textures{ 4 };
constexpr float select_box_movement_minimum_cooldown{ .20f };
constexpr int properties_starting_y_coordinate{ 300 };
constexpr int properties_spacing{ 60 };
constexpr int properties_font_size{ 15 };
constexpr int save_and_exit_y_coordinate{ 525 };
constexpr int end_game_screen_pause_time{ 5 }; // seconds
constexpr int high_scores_x_location{ 250 };
constexpr int high_scores_y_starting_location{ 315 };
constexpr int high_scores_y_spacing{ 35 };
constexpr int high_scores_font_size{ 25 };
constexpr int initails_and_score_spacing{ 100 };
constexpr int initials_first_x_coordinate{ 290 };
constexpr int initials_second_x_coordinate{ 315 };
constexpr int initials_third_x_coordinate{ 340 };
constexpr int initials_y_coordiate{ 375 };
constexpr int initials_x_spacing{ initials_second_x_coordinate - initials_first_x_coordinate };
constexpr int initials_box_x_padding{ 4 };
constexpr Vector2 high_score_select_box_start_location{ initials_first_x_coordinate - initials_box_x_padding, initials_y_coordiate - 2 };

const float demons_x_range[2]{ 5.0f, window_dimensions[1] - (16.f * character_scale) + 5.f}; // First is Left Limit, Second is Right Limit

class GameMap {
	Properties Props{};
	DoubleLinkedList<Property> Visible_properties{};

	// Pregame Properties
	Vector2 Select_box_location{ 165, 190 };
	float Select_box_movement_cooldown{ 3.f };
	int Properties_scroller_offset{ 0 };
	int Property_selector_coordinate{ 1 };
	
	// Game Map Templates
	Texture2D Background;
	Texture2D Midground;
	Texture2D Foreground;

	Texture2D Regular_shield;
	Texture2D Revive_shield;

	// Game Music
	MusicController Music_controller;

	// Character Objects
	Mage mage;
	shared_ptr<Demon> Special_demon; // Can this be a unique_ptr?

	DoubleLinkedList<Projectile> Mage_projectiles{};
	DoubleLinkedList<Projectile> Demon_projectiles{};
	DoubleLinkedList<DoubleLinkedList<Demon>> Demons_columns{};
	DoubleLinkedList<Shield> Shields{};

	bool has_invaded{ false };
	bool has_special_demon_spawned{ false };
	int level{ 0 };
	int demons_moved_down_count{ 0 };
	float time_on_screen{ 0 };

	bool Is_main_screen{ true };
	bool Is_properties_screen{ false };
	bool Is_intro{ false };
	bool Is_game_over_screen{ false };
	bool Is_high_score{ false };
	bool Is_ready_to_confirm_initials{ false };
	bool Is_end_game_requested{ false };

	string High_score_position{ "3" };
	
	void drawPlayerPropertyOptions();
	void drawPlayerMenuOptions();
	void drawNavigationInstructions(bool isPropertiesMenu);
	void drawProperty(shared_ptr<Node<Property>> property);
	void drawPropertyDescription(shared_ptr<Node<Property>> property);
	void drawBackground();
	void drawNewHighScore();
	void drawSaveAndExitOptions();
	void drawLives();
	void drawShieldCount();
	void drawMainScreenBackground();
	void drawMainScreen(map<string, Texture2D> textures, const float dT);
	void drawFloatProperty(float value, int x_position, int y_position);
	void drawBoolProperty(bool value, int x_position, int y_position);
	void drawIntProperty(int value, int x_position, int y_position);
	void checkPropertiesPageUserInput();
	void saveOrRestorDefaults();
	void moveSelectBoxLocationToSaveProperties();
	void moveSelectBoxLocationToGameProperties();
	void moveSelectBoxLocationToGamePlayOptions();
	void updatePropertySelectorCoordinate(int x);
	void populateVisibleProperties();
	void clearVisibleProperties();
	void appendProjectile();
	void appendProjectile(shared_ptr<Demon> demon); 
	void moveMageProjectiles(const float dT);
	void moveDemonProjectiles(const float dT, Mage& mage);
	void moveAllDemons(const float dT, const bool is_main_screen = false);
	void drawHighScores();
	void allDemonCollisionCheckAndAppendDemonProjectiles();
	void checkDemonProjectileForMageProjectilesCollision(shared_ptr<Node<Projectile>> demon_projectiles);
	void checkDemonProjectilForShieldCollision(shared_ptr<Node<Projectile>> demon_projectiles);
	void drawAllShields();
	void mageTakesDamage();
	void generateOrMoveAllShields(const float dT);
	void generateReviveShield();
	void moveReviveShield(const float dT);
	void destroySpecialDemon(const bool is_killed);
	void generateRandomDemon(map<string, Texture2D> textures);
	void updateBackgroundTextures(map<string, Texture2D> textures);
	void setIsGameOverValues();
	void selectInitialsUserInput();
	void confirmInitialsUserInput();
	void drawConfirmationOptions();
	void newHighScoreTick();
	bool shouldNodeBeDeleted();
	bool hasCollision(shared_ptr<Demon> demon);
	bool checkPropertiesPageSaveOptionsInput();
	bool playerMainScreenTick();
	bool playerPropertiesScreenTick();
	shared_ptr<Demon> generateDemonWithRandomTexture(map<string, Texture2D> textures, const int random);
	
	void moveDemonColumn(
		shared_ptr<Node<DoubleLinkedList<Demon>>> column,
		const float dT, 
		const bool is_first_down,
		const bool is_speed_bump,
		const bool is_main_screen = false
	);
	void demonColumnCollisionCheck(
		shared_ptr<Node<DoubleLinkedList<Demon>>> column
	);



public:
	//GameMap(map<string, Texture2D> textures);
	GameMap(map<string, Texture2D> textures, MusicController& music_controller);

	//~GameMap();

	bool hasDemons();
	bool hasInvaded();
	bool getHasSpecialDemonInvaded();
	bool getIsMainScreen();
	bool getIsIntro();
	bool getIsEndGameRequested();
	bool getPropertiesShouldStartGameWithShieldsActive();
	bool getIsPropertiesScreen();
	bool getIsGameOverScreen();
	Mage& getMage();
	MusicController getMusicController();
	void tick(const float dT);
	void generateDemonsList(map<string, Texture2D> textures);
	void generateShields();
	void drawEndGame();
	void generateSpecialDemon(map<string, Texture2D> textures);
	void setHasSpecialDemonInvaded(const bool b);
	void drawInstructions();
	void displayHomeMenu(map<string, Texture2D> textures, const float dT);
	void displayPropertiesMenu(map<string, Texture2D> textures, const float dT);
	bool displayGameOverScreen(const float dT);
	void setIsIntro(const bool b);
	void resetProperties();
	void setResetShieldCountToStartingAmount();
	void clearAllShields();
	int getDemonsMovedDownCount();
};

