#pragma once
#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h" 
#include "rapidjson/writer.h"
#include <memory>
#include <string>
using std::unique_ptr;
using std::string;

extern const bool is_windows_os;

// General Game Properties
constexpr int number_of_starting_lives{ 3 };
constexpr int number_of_starting_shields{ 3 };
constexpr float number_of_texure_updates_rate_per_second{ 1.0f / 12.0f };
constexpr float revive_shield_movement_speed_in_pixels_per_second{ -600 }; // pixels per second


// Demon Properties
constexpr int number_of_demon_columns{ 6 };
constexpr int number_of_rows_before_speed_boost{ 3 };
constexpr int demon_base_points{ 50 };
constexpr int scamp_score_multiplier{ 1 };
constexpr int fledgling_score_multiplier{ 2 };
constexpr int skull_score_multiplier{ 3 };
constexpr int eye_score_multipler{ 10 };

// Demon Mechanic Properties
constexpr float demon_base_speed_in_pixels_per_second{ 50.0 }; // pixels per second 
constexpr float demon_acceleration_in_pixels_per_second{ 10.0f }; // pixels per second
constexpr float demon_level_acceleration_percentage{ 1.25 }; // 
constexpr float demon_attack_rate_in_seconds{ 3.f }; // How long a demon will pause after an attack before looking to attack again
constexpr float demon_projectile_speed_in_pixels_per_second{ 150.f }; // pixels per second
constexpr int demon_attack_chance_percentage{ 20 }; // This is a percentage (aka, divided by 100)

// Mage Properties 
constexpr float attack_texture_update_rate_per_second{ 1.0f / 18.0f };
constexpr float casting_shield_texutre_update_rate_per_second{ 1.0f / 12.0f };
constexpr float mage_speed_in_pixels_per_second{ 200.f }; // pixels per second
constexpr float mage_attack_rate_per_second{ .15 }; // seconds per attack
constexpr float mage_projectile_speed_in_pixels_per_second{ 300.f }; // pixels per second


class Properties {
	rapidjson::Document Properties_document;

	// General Game Properties
	int Number_of_starting_lives;
	int Number_of_starting_shields;
	float Number_of_texure_updates_rate_per_second; // The number of times a characters texture is updated per second
	float Revive_shield_movement_speed_in_pixels_per_second; // How quickly the revive shield moves across the map after a mage death

	// Demon Properties
	int Number_of_demon_columns;
	int Number_of_rows_before_speed_boost;
	int Demon_base_points;
	int Scamp_score_multiplier;
	int Fledgling_score_multiplier;
	int Skull_score_multiplier;
	int Eye_score_multipler;


	// Demon Mechanic Properties
	float Demon_base_speed_in_pixels_per_second;
	float Demon_acceleration_in_pixels_per_second;
	float Demon_level_acceleration_multiplier;
	float Demon_attack_rate_in_seconds; // How long a demon will pause after an attack before looking to attack again
	float Demon_projectile_speed_in_pixels_per_second;
	int Demon_attack_chance_percentage; // The chance a ready demon will attack

	// Mage Properties 
	float Attack_texture_update_rate_per_second; // The number of times the mages texture is updated per second during its attack animation
	float Casting_shield_texutre_update_rate_per_second; // The number of times the mages texture is updated per second during its shield casting animation
	float Mage_speed_in_pixels_per_second;
	float Mage_attack_rate_per_second; // The number of attacks a mage can fit in per second
	float Mage_projectile_speed_in_pixels_per_second;
	
public:
	Properties();
	void saveProperties();
	void restoreDefaults();
	void updateIntProperty(string key, int value);
	void updateFloatProperty(string key, float value);

	int getNumberOfStartingLives();
	int getNumberOfStartingShields();
	float getNumberOfTexureUpdatesRatePerSecond();
	float getReviveShieldMovementSpeedInPixelsPerSecond();
	int getNumberOfDemonColumns();
	int getNumberOfRowsBeforeSpeedBoost();
	int getDemonBasePoints();
	int getScampScoreMultiplier();
	int getFledglingScoreMultiplier();
	int getSkullScoreMultiplier();
	int getEyeScoreMultipler();
	float getDemonBaseSpeedInPixelsPerSecond();
	float getDemonAccelerationInPixelsPerSecond();
	float getDemonLevelAccelerationMultiplier();
	float getDemonAttackRateInSeconds();
	float getDemonProjectileSpeedInPixelsPerSecond();
	int getDemonAttackChancePercentage();
	float getAttackTextureUpdateRatePerSecond();
	float getCastingShieldTexutreUpdateRatePerSecond();
	float getMageSpeedInPixelsPerSecond();
	float getMageAttackRatePerSecond();
	float getMageProjectileSpeedInPixelsPerSecond();
};

