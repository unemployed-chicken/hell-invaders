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
using std::make_pair;
using std::make_shared;

extern const bool is_windows_os;

// General Game Properties
constexpr int number_of_starting_lives{ 3 };
constexpr int number_of_starting_shields{ 3 };
constexpr float number_of_texure_updates_rate_per_second{ 1.0f / 12.0f }; // TODO: Change this to 12 and divide 1 by this number in code
constexpr float revive_shield_movement_speed_in_pixels_per_second{ 600 }; // pixels per second // TODO: Make this Positive
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
constexpr float demon_base_speed_in_pixels_per_second{ 50.0 }; // pixels per second 
constexpr int demon_acceleration_in_pixels_per_second{ 5 }; // pixels per second
constexpr int demon_level_acceleration_in_pixels_per_second{ 10 }; // TODO: Make this an int
constexpr int demon_projectile_speed_in_pixels_per_second{ 150 }; // pixels per second
constexpr float demon_attack_rate_in_milliseconds{ 3000.f }; // How long a demon will pause after an attack before looking to attack again //TODO: Convert to Milliseconds
constexpr int demon_attack_chance_percentage{ 20 }; // This is a percentage (aka, divided by 100)

// Mage Properties 
constexpr float attack_texture_update_rate_per_second{ 1.0f / 18.0f };
constexpr float casting_shield_texture_update_rate_per_second{ 1.0f / 12.0f };
constexpr float mage_speed_in_pixels_per_second{ 200.f }; // pixels per second
constexpr int mage_attack_rate_in_millisecond{ 150 }; // milliseconds per attack
constexpr float mage_projectile_speed_in_pixels_per_second{ 300.f }; // pixels per second


class Property {
	string Key;
	float Value;
	float Default_value;
	string Description{}; // TODO: Define this logic
	string Name{}; // TODO: Define this logic
	int Increment_counter{ 1 }; // TODO: Define this logic
	int Location;
	bool IsFloat;
	bool IsBool;

public:
	Property(string key, float value, int location, string description, string name, int increment_counter, float default_value);
	Property(string key, int value, int location, string description, string name, int increment_counter, int default_value);
	Property(string key, bool value, int location, string description, string name, int increment_counter, bool default_value);
	Property();
	void setKey(string key);
	void setValue(float value);
	void setLocation(int location);
	void incrementValue(int direction);
	string getKey();
	float getValue();
	int getLocation();
	int getPropertyWidth(int font_size);
	bool getIsFloat();
	bool getIsBool();
};


class Properties {
	rapidjson::Document Properties_document;
	map<string, shared_ptr<Node<Property>>> Props{};
	int count{ 0 };

	int genertateIntProperty(string document_key, string props_key, int default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details);
	int genertateBoolProperty(string document_key, string props_key, bool default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details);
	int genertateFloatProperty(string document_key, string props_key, float default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details);
	void assignPreviousandNext(shared_ptr<Node<Property>> previous, shared_ptr<Node<Property>> next);
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

	bool getBoolPropertyValue(string property);
	int getIntPropertyValue(string property);
	float getFloatPropertyValue(string property);
	shared_ptr<Node<Property>> getPropertyByPosition(int property_position);
	shared_ptr<Node<Property>> getPropertyByName(string property); 
};
