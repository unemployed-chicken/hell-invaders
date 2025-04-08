#pragma once
#include "DoubleLinkedList.h"
#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h" 
#include "rapidjson/writer.h"
#include <algorithm>
#include <map>
#include <memory>
#include <string>
using std::map;
using std::string;
using std::pair;
using std::make_pair;
using std::make_shared;

extern const bool is_windows_os;

// General Game Properties
constexpr int number_of_starting_lives{ 3 };
constexpr int number_of_starting_shields{ 3 };
constexpr int number_of_texure_updates_rate_per_second{ 12 };
constexpr int revive_shield_movement_speed_in_pixels_per_second{ 600 }; // pixels per second
constexpr bool should_skip_intro{ false };
constexpr bool should_start_with_shields_active{ true };
constexpr bool should_projectiles_collide{ true };
constexpr bool is_music_on{ true };

// Demon Properties
constexpr int number_of_demon_columns{ 6 };
constexpr int number_of_rows_before_speed_boost{ 3 };
constexpr int demon_base_points{ 50 };
constexpr int scamp_score_multiplier{ 1 };
constexpr int fledgling_score_multiplier{ 2 };
constexpr int skull_score_multiplier{ 3 };
constexpr int eye_score_multipler{ 10 };

// Demon Mechanic Properties
constexpr int demon_base_speed_in_pixels_per_second{ 50 }; // pixels per second 
constexpr int demon_acceleration_in_pixels_per_second{ 5 }; // pixels per second
constexpr int demon_level_acceleration_in_pixels_per_second{ 10 };
constexpr int demon_projectile_speed_in_pixels_per_second{ 150 }; // pixels per second
constexpr int demon_attack_rate_in_milliseconds{ 3000 }; // How long a demon will pause after an attack before looking to attack again
constexpr int demon_attack_chance_percentage{ 20 }; // This is a percentage (aka, divided by 100)

// Mage Properties 
constexpr int attack_texture_update_rate_per_second{ 18 };
constexpr int casting_shield_texture_update_rate_per_second{ 12 };
constexpr int mage_speed_in_pixels_per_second{ 200 }; // pixels per second
constexpr int mage_attack_rate_in_millisecond{ 150 }; // milliseconds per attack
constexpr int mage_projectile_speed_in_pixels_per_second{ 300 }; // pixels per second


class Property {
	string Key;
	float Value;
	int Default_value;
	int Min_value{ 1 };
	int Max_value{ 100 };
	string Description{"None"};
	string Name{"None"};
	int Increment_counter{ 1 };
	int Location;
	bool IsFloat;
	bool IsBool;

	void assignDetails(rapidjson::Document& details, string key);

public:
	Property(string key, float value, int location, float default_value, rapidjson::Document& details);
	Property(string key, int value, int location, int defualt_value, rapidjson::Document& details);
	Property(string key, bool value, int location, bool default_value, rapidjson::Document& details);
	Property();
	void setKey(string key);
	void setValue(float value);
	void setLocation(int location);
	void incrementValue(int direction);
	string getKey();
	float getValue();
	int getLocation();
	bool getIsFloat();
	bool getIsBool();
	int getMinValue();
	int getMaxValue();
	int getDefaultValue();
	string getDescription();
	string getName();
	int getIncrementCounter();
};


class Properties {
	rapidjson::Document High_scores;
	rapidjson::Document Properties_document;
	map<string, shared_ptr<Node<Property>>> Props{};
	int count{ 0 };

	int genertateIntProperty(string document_key, string props_key, int default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details);
	int genertateBoolProperty(string document_key, string props_key, bool default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details);
	//int genertateFloatProperty(string document_key, string props_key, float default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details);
	void assignPreviousandNext(shared_ptr<Node<Property>> previous, shared_ptr<Node<Property>> next);
	void generateHighScores();
	rapidjson::Document generatePropertyDescriptions();

public:
	Properties(rapidjson::Document& properties_details_document);
	Properties();
	void saveProperties();
	void restoreDefaults();
	void updateIntProperty(string key, int value);
	void updateBoolProperty(string key, bool value);
	void updateFloatProperty(string key, float value);

	int getCount();

	bool getBoolPropertyValue(const string property);
	int getIntPropertyValue(const string property);
	float getFloatPropertyValue(const string property);
	float getPerSecondPropertyValue(const string property);
	std::pair<string, int> getScore(const string position);
	shared_ptr<Node<Property>> getPropertyByPosition(int property_position);
	shared_ptr<Node<Property>> getPropertyByName(string property); 
};
