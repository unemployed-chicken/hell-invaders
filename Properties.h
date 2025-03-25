#pragma once
#include "DoubleLinkedList.h"
#include "rapidjson/document.h" 
#include "rapidjson/filereadstream.h" 
#include "rapidjson/filewritestream.h" 
#include "rapidjson/writer.h"
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
constexpr float number_of_texure_updates_rate_per_second{ 1.0f / 12.0f };
constexpr float revive_shield_movement_speed_in_pixels_per_second{ -600 }; // pixels per second
constexpr float should_skip_intro{ false };
constexpr float should_start_with_shields_active{ true };


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


class Property {
	string Key;
	float Value;
	int Location;
	bool IsFloat;
	bool IsBool;

public:
	Property(string key, float value, int location);
	Property(string key, int value, int location);
	Property(string key, bool value, int location);
	Property();
	void setKey(string key);
	void setValue(float value);
	void setLocation(int location);
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

	int genertateIntProperty(string document_key, string props_key, int default_value, int count, shared_ptr<Node<Property>> previous);
	int genertateBoolProperty(string document_key, string props_key, bool default_value, int count, shared_ptr<Node<Property>> previous);
	int genertateFloatProperty(string document_key, string props_key, float default_value, int count, shared_ptr<Node<Property>> previous);
	void assignPreviousandNext(shared_ptr<Node<Property>> previous, shared_ptr<Node<Property>> next);

public:
	Properties();
	void saveProperties();
	void restoreDefaults();
	void updateIntProperty(string key, int value);
	void updateFloatProperty(string key, float value);

	int getCount();

	bool getBoolPropertyValue(string property);
	int getIntPropertyValue(string property);
	float getFloatPropertyValue(string property);
	shared_ptr<Node<Property>> getPropertyByPosition(int property_position); // TODO: Define This
	shared_ptr<Node<Property>> getPropertyByName(string property); // TODO: Define This
};
