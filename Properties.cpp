#include "Properties.h"

Properties::Properties() {
	FILE* fp;
    is_windows_os ? fopen_s(&fp, "user_defined_properties.json", "rb") : fopen_s(&fp, "user_defined_properties.json", "r"); // non-Windows use "r" 

    if (fp) {
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        Properties_document.ParseStream(is);
        fclose(fp);
    }
    else {
        Properties_document.SetObject();
    }

    if (Properties_document.HasParseError() || !Properties_document.IsObject()) {
        // Possible logger message here: cout << "Error reading JSON file. Creating a new JSON object.\n";
        Properties_document.SetObject();
    }
    
    // General Game Properties
    Properties_document.HasMember("number_of_starting_lives") ? Number_of_starting_lives = Properties_document["number_of_starting_lives"].GetInt() : Number_of_starting_lives = number_of_starting_lives;
    Properties_document.HasMember("number_of_starting_shields") ? Number_of_starting_shields = Properties_document["number_of_starting_shields"].GetInt() : Number_of_starting_shields = number_of_starting_shields;
    Properties_document.HasMember("number_of_texure_updates_rate_per_second") ? Number_of_texure_updates_rate_per_second = Properties_document["number_of_texure_updates_rate_per_second"].GetFloat() : Number_of_texure_updates_rate_per_second = number_of_texure_updates_rate_per_second;
    Properties_document.HasMember("revive_shield_movement_speed_in_pixels_per_second") ? Revive_shield_movement_speed_in_pixels_per_second = Properties_document["revive_shield_movement_speed_in_pixels_per_second"].GetFloat() : Revive_shield_movement_speed_in_pixels_per_second = revive_shield_movement_speed_in_pixels_per_second;

    // Demon Properties
    Properties_document.HasMember("number_of_demon_columns") ? Number_of_demon_columns = Properties_document["number_of_demon_columns"].GetInt() : Number_of_demon_columns = number_of_demon_columns;
    Properties_document.HasMember("number_of_rows_before_speed_boost") ? Number_of_rows_before_speed_boost = Properties_document["number_of_rows_before_speed_boost"].GetInt() : Number_of_rows_before_speed_boost = number_of_rows_before_speed_boost;
    Properties_document.HasMember("demon_base_points") ? Demon_base_points = Properties_document["demon_base_points"].GetInt() : Demon_base_points = demon_base_points;
    Properties_document.HasMember("scamp_score_multiplier") ? Scamp_score_multiplier = Properties_document["scamp_score_multiplier"].GetInt() : Scamp_score_multiplier = scamp_score_multiplier;
    Properties_document.HasMember("fledgling_score_multiplier") ? Fledgling_score_multiplier = Properties_document["fledgling_score_multiplier"].GetInt() : Fledgling_score_multiplier = fledgling_score_multiplier;
    Properties_document.HasMember("skull_score_multiplier") ? Skull_score_multiplier = Properties_document["skull_score_multiplier"].GetInt() : Skull_score_multiplier = skull_score_multiplier;
    Properties_document.HasMember("eye_score_multipler") ? Eye_score_multipler = Properties_document["eye_score_multipler"].GetInt() : Eye_score_multipler = eye_score_multipler;

    // Demon Mechanic Properties
    Properties_document.HasMember("demon_base_speed_in_pixels_per_second") ? Demon_base_speed_in_pixels_per_second = Properties_document["demon_base_speed_in_pixels_per_second"].GetFloat() : Demon_base_speed_in_pixels_per_second = demon_base_speed_in_pixels_per_second;
    Properties_document.HasMember("demon_acceleration_in_pixels_per_second") ? Demon_acceleration_in_pixels_per_second = Properties_document["demon_acceleration_in_pixels_per_second"].GetFloat() : Demon_acceleration_in_pixels_per_second = demon_acceleration_in_pixels_per_second;
    Properties_document.HasMember("demon_attack_rate_in_seconds") ? Demon_attack_rate_in_seconds = Properties_document["demon_attack_rate_in_seconds"].GetFloat() : Demon_attack_rate_in_seconds = demon_attack_rate_in_seconds;
    Properties_document.HasMember("demon_projectile_speed_in_pixels_per_second") ? Demon_projectile_speed_in_pixels_per_second = Properties_document["demon_projectile_speed_in_pixels_per_second"].GetFloat() : Demon_projectile_speed_in_pixels_per_second = demon_projectile_speed_in_pixels_per_second;
    Properties_document.HasMember("demon_attack_chance_percentage") ? Demon_attack_chance_percentage = Properties_document["demon_attack_chance_percentage"].GetInt() : Demon_attack_chance_percentage = demon_attack_chance_percentage;

    // Mage Properties
    Properties_document.HasMember("attack_texture_update_rate_per_second") ? Attack_texture_update_rate_per_second = Properties_document["attack_texture_update_rate_per_second"].GetFloat() : Attack_texture_update_rate_per_second = attack_texture_update_rate_per_second;
    Properties_document.HasMember("casting_shield_texutre_update_rate_per_second") ? Casting_shield_texutre_update_rate_per_second = Properties_document["casting_shield_texutre_update_rate_per_second"].GetFloat() : Casting_shield_texutre_update_rate_per_second = casting_shield_texutre_update_rate_per_second;
    Properties_document.HasMember("mage_speed_in_pixels_per_second") ? Mage_speed_in_pixels_per_second = Properties_document["mage_speed_in_pixels_per_second"].GetFloat() : Mage_speed_in_pixels_per_second = mage_speed_in_pixels_per_second;
    Properties_document.HasMember("mage_attack_rate_per_second") ? Mage_attack_rate_per_second = Properties_document["mage_attack_rate_per_second"].GetFloat() : Mage_attack_rate_per_second = mage_attack_rate_per_second;
    Properties_document.HasMember("mage_projectile_speed_in_pixels_per_second") ? Mage_projectile_speed_in_pixels_per_second = Properties_document["mage_projectile_speed_in_pixels_per_second"].GetFloat() : Mage_projectile_speed_in_pixels_per_second = mage_projectile_speed_in_pixels_per_second;


}

void Properties::saveProperties() {
    FILE* fp;
    is_windows_os ? fopen_s(&fp, "user_defined_properties.json", "wb") : fopen_s(&fp, "user_defined_properties.json", "w"); // non-Windows use "w" 

    if (fp) {
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer,
            sizeof(writeBuffer));
        rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
        Properties_document.Accept(writer);
        fclose(fp);
    }
}

void Properties::restoreDefaults() {
    Properties_document.Clear();
    saveProperties();
}

void Properties::updateIntProperty(string key, int value) {
    if (Properties_document.HasMember(key.c_str())) {
        rapidjson::Value& property = Properties_document[key.c_str()];
        property.SetInt(value);
    }
    else {
        rapidjson::Value v_key(rapidjson::StringRef(key.c_str()));
        rapidjson::Value v_value(value); 
        Properties_document.AddMember(v_key, v_value, Properties_document.GetAllocator());
    }
}

void Properties::updateFloatProperty(string key, float value) {
    if (Properties_document.HasMember(key.c_str())) {
        rapidjson::Value& property = Properties_document[key.c_str()];
        property.SetFloat(value);
    }
    else {
        rapidjson::Value v_key(rapidjson::StringRef(key.c_str()));
        Properties_document.AddMember(v_key, value, Properties_document.GetAllocator());
    }
}

int Properties::getNumberOfStartingLives() { return Number_of_starting_lives; }
int Properties::getNumberOfStartingShields() { return Number_of_starting_shields; }
float Properties::getNumberOfTexureUpdatesRatePerSecond() { return Number_of_texure_updates_rate_per_second; }
float Properties::getReviveShieldMovementSpeedInPixelsPerSecond() { return Revive_shield_movement_speed_in_pixels_per_second; }
int Properties::getNumberOfDemonColumns() { return Number_of_demon_columns; }
int Properties::getNumberOfRowsBeforeSpeedBoost() { return Number_of_rows_before_speed_boost; }
int Properties::getDemonBasePoints() { return Demon_base_points; }
int Properties::getScampScoreMultiplier() { return Scamp_score_multiplier; }
int Properties::getFledglingScoreMultiplier() { return Fledgling_score_multiplier; }
int Properties::getSkullScoreMultiplier() { return Skull_score_multiplier; }
int Properties::getEyeScoreMultipler() { return Eye_score_multipler; }
float Properties::getDemonBaseSpeedInPixelsPerSecond() { return Demon_base_speed_in_pixels_per_second; }
float Properties::getDemonAccelerationInPixelsPerSecond() { return Demon_acceleration_in_pixels_per_second; }
float Properties::getDemonLevelAccelerationMultiplier() { return Demon_level_acceleration_multiplier; }
float Properties::getDemonAttackRateInSeconds() { return Demon_attack_rate_in_seconds; }
float Properties::getDemonProjectileSpeedInPixelsPerSecond() { return Demon_projectile_speed_in_pixels_per_second; }
int Properties::getDemonAttackChancePercentage() { return Demon_attack_chance_percentage; }
float Properties::getAttackTextureUpdateRatePerSecond() { return Attack_texture_update_rate_per_second; }
float Properties::getCastingShieldTexutreUpdateRatePerSecond() { return Casting_shield_texutre_update_rate_per_second; }
float Properties::getMageSpeedInPixelsPerSecond() { return Mage_speed_in_pixels_per_second; }
float Properties::getMageAttackRatePerSecond() { return Mage_attack_rate_per_second; }
float Properties::getMageProjectileSpeedInPixelsPerSecond() { return Mage_projectile_speed_in_pixels_per_second; }


/*
* Workflow for Properties: 
*    Created on GameMap where it reads the predefined values and stores those that exists.
*    If They do not exist, the vaules are grabbed from default.
*    If a user wants to change the values, they can set an individual one in the document. 
*        - If all changes are confirmed, they written to the properties.json file.
*               - Properties object is recreated from scratch. (see above workflow)
*        - If a user decides to cancel their changes, they can cancel. The file is not saved. 
*               - Properties object is recreated from scratch.
*    A user can reset all custom changes by restoreDefaults(). 
*        - Properties object is recreated from scratch.
*    
*/

