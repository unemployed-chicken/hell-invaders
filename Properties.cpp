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
    
    int i{ 1 };

    // General Game Properties
    int Number_of_starting_lives;
    Properties_document.HasMember("number_of_starting_lives") ? Number_of_starting_lives = Properties_document["number_of_starting_lives"].GetInt() : Number_of_starting_lives = number_of_starting_lives;
    Props["Number_of_starting_lives"] = Property("Number_of_starting_lives", static_cast<float>(Number_of_starting_lives), i);

    i++;
    int Number_of_starting_shields;
    Properties_document.HasMember("number_of_starting_shields") ? Number_of_starting_shields = Properties_document["number_of_starting_shields"].GetInt() : Number_of_starting_shields = number_of_starting_shields;
    Props["Number_of_starting_shields"] = Property("Number_of_starting_shields", static_cast<float>(Number_of_starting_shields), i);
    
    i++;
    float Number_of_texure_updates_rate_per_second;
    Properties_document.HasMember("number_of_texure_updates_rate_per_second") ? Number_of_texure_updates_rate_per_second = Properties_document["number_of_texure_updates_rate_per_second"].GetFloat() : Number_of_texure_updates_rate_per_second = number_of_texure_updates_rate_per_second;
    Props["Number_of_texure_updates_rate_per_second"] = Property("Number_of_texure_updates_rate_per_second", Number_of_texure_updates_rate_per_second, i);
    
    i++;
    float Revive_shield_movement_speed_in_pixels_per_second;
    Properties_document.HasMember("revive_shield_movement_speed_in_pixels_per_second") ? Revive_shield_movement_speed_in_pixels_per_second = Properties_document["revive_shield_movement_speed_in_pixels_per_second"].GetFloat() : Revive_shield_movement_speed_in_pixels_per_second = revive_shield_movement_speed_in_pixels_per_second;
    Props["Revive_shield_movement_speed_in_pixels_per_second"] = Property("Revive_shield_movement_speed_in_pixels_per_second", Revive_shield_movement_speed_in_pixels_per_second, i);

    i++;
    bool Should_skip_intro;
    Properties_document.HasMember("should_skip_intro") ? Should_skip_intro = Properties_document["should_skip_intro"].GetBool() : Should_skip_intro = should_skip_intro;
    Props["Should_skip_intro"] = Property("Should_skip_intro", static_cast<float>(Should_skip_intro), i);
    
    i++;
    bool Should_start_with_shields_active;
    Properties_document.HasMember("should_start_with_shields_active") ? Should_start_with_shields_active = Properties_document["should_start_with_shields_active"].GetBool() : Should_start_with_shields_active = should_start_with_shields_active;
    Props["Should_start_with_shields_active"] = Property("Should_start_with_shields_active", static_cast<float>(Should_start_with_shields_active), i);


    // Demon Properties
    i++;
    int Number_of_demon_columns;
    Properties_document.HasMember("number_of_demon_columns") ? Number_of_demon_columns = Properties_document["number_of_demon_columns"].GetInt() : Number_of_demon_columns = number_of_demon_columns;
    Props["Number_of_demon_columns"] = Property("Number_of_demon_columns", static_cast<float>(Number_of_demon_columns), i);

    i++;
    int Number_of_rows_before_speed_boost;
    Properties_document.HasMember("number_of_rows_before_speed_boost") ? Number_of_rows_before_speed_boost = Properties_document["number_of_rows_before_speed_boost"].GetInt() : Number_of_rows_before_speed_boost = number_of_rows_before_speed_boost;
    Props["Number_of_rows_before_speed_boost"] = Property("Number_of_rows_before_speed_boost", static_cast<float>(Number_of_rows_before_speed_boost), i);

    i++;
    int Demon_base_points;
    Properties_document.HasMember("demon_base_points") ? Demon_base_points = Properties_document["demon_base_points"].GetInt() : Demon_base_points = demon_base_points;
    Props["Demon_base_points"] = Property("Demon_base_points", static_cast<float>(Demon_base_points), i);

    i++;
    int Scamp_score_multiplier;
    Properties_document.HasMember("scamp_score_multiplier") ? Scamp_score_multiplier = Properties_document["scamp_score_multiplier"].GetInt() : Scamp_score_multiplier = scamp_score_multiplier;
    Props["Scamp_score_multiplier"] = Property("Scamp_score_multiplier", static_cast<float>(Scamp_score_multiplier), i);

    i++;
    int Fledgling_score_multiplier;
    Properties_document.HasMember("fledgling_score_multiplier") ? Fledgling_score_multiplier = Properties_document["fledgling_score_multiplier"].GetInt() : Fledgling_score_multiplier = fledgling_score_multiplier;
    Props["Fledgling_score_multiplier"] = Property("Fledgling_score_multiplier", static_cast<float>(Fledgling_score_multiplier), i);

    i++;
    int Skull_score_multiplier;
    Properties_document.HasMember("skull_score_multiplier") ? Skull_score_multiplier = Properties_document["skull_score_multiplier"].GetInt() : Skull_score_multiplier = skull_score_multiplier;
    Props["Skull_score_multiplier"] = Property("Skull_score_multiplier", static_cast<float>(Skull_score_multiplier), i);

    i++;
    int Eye_score_multipler;
    Properties_document.HasMember("eye_score_multipler") ? Eye_score_multipler = Properties_document["eye_score_multipler"].GetInt() : Eye_score_multipler = eye_score_multipler;
    Props["Eye_score_multipler"] = Property("Eye_score_multipler", static_cast<float>(Eye_score_multipler), i);


    // Demon Mechanic Properties
    i++;
    float Demon_base_speed_in_pixels_per_second;
    Properties_document.HasMember("demon_base_speed_in_pixels_per_second") ? Demon_base_speed_in_pixels_per_second = Properties_document["demon_base_speed_in_pixels_per_second"].GetFloat() : Demon_base_speed_in_pixels_per_second = demon_base_speed_in_pixels_per_second;
    Props["Demon_base_speed_in_pixels_per_second"] = Property("Demon_base_speed_in_pixels_per_second", Demon_base_speed_in_pixels_per_second, i);

    i++;
    float Demon_acceleration_in_pixels_per_second;
    Properties_document.HasMember("demon_acceleration_in_pixels_per_second") ? Demon_acceleration_in_pixels_per_second = Properties_document["demon_acceleration_in_pixels_per_second"].GetFloat() : Demon_acceleration_in_pixels_per_second = demon_acceleration_in_pixels_per_second;
    Props["Demon_acceleration_in_pixels_per_second"] = Property("Demon_acceleration_in_pixels_per_second", Demon_acceleration_in_pixels_per_second, i);

    i++;
    float Demon_level_acceleration_percentage;
    Properties_document.HasMember("demon_level_acceleration_percentage") ? Demon_level_acceleration_percentage = Properties_document["demon_level_acceleration_percentage"].GetFloat() : Demon_level_acceleration_percentage = demon_level_acceleration_percentage;
    Props["Demon_level_acceleration_percentage"] = Property("Demon_level_acceleration_percentage", Demon_level_acceleration_percentage, i);

    i++;
    float Demon_attack_rate_in_seconds;
    Properties_document.HasMember("demon_attack_rate_in_seconds") ? Demon_attack_rate_in_seconds = Properties_document["demon_attack_rate_in_seconds"].GetFloat() : Demon_attack_rate_in_seconds = demon_attack_rate_in_seconds;
    Props["Demon_attack_rate_in_seconds"] = Property("Demon_attack_rate_in_seconds", Demon_attack_rate_in_seconds, i);

    i++;
    float Demon_projectile_speed_in_pixels_per_second;
    Properties_document.HasMember("demon_projectile_speed_in_pixels_per_second") ? Demon_projectile_speed_in_pixels_per_second = Properties_document["demon_projectile_speed_in_pixels_per_second"].GetFloat() : Demon_projectile_speed_in_pixels_per_second = demon_projectile_speed_in_pixels_per_second;
    Props["Demon_projectile_speed_in_pixels_per_second"] = Property("Demon_projectile_speed_in_pixels_per_second", Demon_projectile_speed_in_pixels_per_second, i);

    i++;
    int Demon_attack_chance_percentage;
    Properties_document.HasMember("demon_attack_chance_percentage") ? Demon_attack_chance_percentage = Properties_document["demon_attack_chance_percentage"].GetInt() : Demon_attack_chance_percentage = demon_attack_chance_percentage;
    Props["Demon_attack_chance_percentage"] = Property("Demon_attack_chance_percentage", static_cast<float>(Demon_attack_chance_percentage), i);


    // Mage Properties
    i++;
    float Attack_texture_update_rate_per_second;
    Properties_document.HasMember("attack_texture_update_rate_per_second") ? Attack_texture_update_rate_per_second = Properties_document["attack_texture_update_rate_per_second"].GetFloat() : Attack_texture_update_rate_per_second = attack_texture_update_rate_per_second;
    Props["Attack_texture_update_rate_per_second"] = Property("Attack_texture_update_rate_per_second", Attack_texture_update_rate_per_second, i);

    i++;
    float Casting_shield_texutre_update_rate_per_second;
    Properties_document.HasMember("casting_shield_texutre_update_rate_per_second") ? Casting_shield_texutre_update_rate_per_second = Properties_document["casting_shield_texutre_update_rate_per_second"].GetFloat() : Casting_shield_texutre_update_rate_per_second = casting_shield_texutre_update_rate_per_second;
    Props["Casting_shield_texutre_update_rate_per_second"] = Property("Casting_shield_texutre_update_rate_per_second", Casting_shield_texutre_update_rate_per_second, i);

    i++;
    float Mage_speed_in_pixels_per_second;
    Properties_document.HasMember("mage_speed_in_pixels_per_second") ? Mage_speed_in_pixels_per_second = Properties_document["mage_speed_in_pixels_per_second"].GetFloat() : Mage_speed_in_pixels_per_second = mage_speed_in_pixels_per_second;
    Props["Mage_speed_in_pixels_per_second"] = Property("Mage_speed_in_pixels_per_second", Mage_speed_in_pixels_per_second, i);

    i++;
    float Mage_attack_rate_per_second;
    Properties_document.HasMember("mage_attack_rate_per_second") ? Mage_attack_rate_per_second = Properties_document["mage_attack_rate_per_second"].GetFloat() : Mage_attack_rate_per_second = mage_attack_rate_per_second;
    Props["Mage_attack_rate_per_second"] = Property("Mage_attack_rate_per_second", Mage_attack_rate_per_second, i);

    i++;
    float Mage_projectile_speed_in_pixels_per_second;
    Properties_document.HasMember("mage_projectile_speed_in_pixels_per_second") ? Mage_projectile_speed_in_pixels_per_second = Properties_document["mage_projectile_speed_in_pixels_per_second"].GetFloat() : Mage_projectile_speed_in_pixels_per_second = mage_projectile_speed_in_pixels_per_second;
    Props["Mage_projectile_speed_in_pixels_per_second"] = Property("Mage_projectile_speed_in_pixels_per_second", Mage_projectile_speed_in_pixels_per_second, i);
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

bool Properties::getBoolPropertyValue(string property) { return static_cast<bool>(Props[property].getValue()); }
int Properties::getIntPropertyValue(string property) { return static_cast<int>(Props[property].getValue()); }
float Properties::getFloatPropertyValue(string property) { return Props[property].getValue(); }

//string Properties::getNameOfPropertyAtPositionX(int position_x) { return string(); } // This ones a bit more intensive;




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

Property::Property(string key, float value, int location) : Key(key), Value(value), Location(location) {}
void Property::setKey(string key) { Key = key; }
void Property::setValue(float value) { Value = value; }
void Property::setLocation(int location) { Location = location; }
string Property::getKey() { return Key; }
float Property::getValue(){ return Value; }
int Property::getLocation() { return Location; }
