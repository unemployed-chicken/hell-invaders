#include "Properties.h"

void Properties::assignPreviousandNext(shared_ptr<Node<Property>> previous, shared_ptr<Node<Property>> next) {
	if (previous) { previous->Next = next; }
	if (next) {	next->Previous = previous; }
}

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
    
    int i{ 0 };

    // General Game Properties
    i = genertateIntProperty("number_of_starting_lives", "Number_of_starting_lives", number_of_starting_lives, i, nullptr);
	i = genertateIntProperty("number_of_starting_shields", "Number_of_starting_shields", number_of_starting_shields, i, Props["Number_of_starting_lives"]);
	i = genertateFloatProperty("number_of_texure_updates_rate_per_second", "Number_of_texure_updates_rate_per_second", number_of_texure_updates_rate_per_second, i, Props["Number_of_starting_shields"]);
	i = genertateFloatProperty("revive_shield_movement_speed_in_pixels_per_second", "Revive_shield_movement_speed_in_pixels_per_second", revive_shield_movement_speed_in_pixels_per_second, i, Props["Number_of_texure_updates_rate_per_second"]);
	i = genertateBoolProperty("should_skip_intro", "Should_skip_intro", should_skip_intro, i, Props["Revive_shield_movement_speed_in_pixels_per_second"]);
	i = genertateBoolProperty("should_start_with_shields_active", "Should_start_with_shields_active", should_start_with_shields_active, i, Props["Should_skip_intro"]);
    
	// Demon Properties
	i = genertateIntProperty("number_of_demon_columns", "Number_of_demon_columns", number_of_demon_columns, i, Props["Should_start_with_shields_active"]);
	i = genertateIntProperty("number_of_rows_before_speed_boost", "Number_of_rows_before_speed_boost", number_of_rows_before_speed_boost, i, Props["Number_of_demon_columns"]);
	i = genertateIntProperty("demon_base_points", "Demon_base_points", demon_base_points, i, Props["Number_of_rows_before_speed_boost"]);
	i = genertateIntProperty("scamp_score_multiplier", "Scamp_score_multiplier", scamp_score_multiplier, i, Props["Demon_base_points"]);
	i = genertateIntProperty("fledgling_score_multiplier", "Fledgling_score_multiplier", fledgling_score_multiplier, i, Props["Scamp_score_multiplier"]);
	i = genertateIntProperty("skull_score_multiplier", "Skull_score_multiplier", skull_score_multiplier, i, Props["Fledgling_score_multiplier"]);
	i = genertateIntProperty("eye_score_multipler", "Eye_score_multipler", eye_score_multipler, i, Props["Skull_score_multiplier"]);

    // Demon Mechanic Properties
	i = genertateFloatProperty("demon_base_speed_in_pixels_per_second", "Demon_base_speed_in_pixels_per_second", demon_base_speed_in_pixels_per_second, i, Props["Eye_score_multipler"]);
	i = genertateFloatProperty("demon_acceleration_in_pixels_per_second", "Demon_acceleration_in_pixels_per_second", demon_acceleration_in_pixels_per_second, i, Props["Demon_base_speed_in_pixels_per_second"]);
	i = genertateFloatProperty("demon_level_acceleration_percentage", "Demon_level_acceleration_percentage", demon_level_acceleration_percentage, i, Props["Demon_acceleration_in_pixels_per_second"]);
	i = genertateFloatProperty("demon_attack_rate_in_seconds", "Demon_attack_rate_in_seconds", demon_attack_rate_in_seconds, i, Props["Demon_level_acceleration_percentage"]);
	i = genertateFloatProperty("demon_projectile_speed_in_pixels_per_second", "Demon_projectile_speed_in_pixels_per_second", demon_projectile_speed_in_pixels_per_second, i, Props["Demon_attack_rate_in_seconds"]);
	i = genertateIntProperty("demon_attack_chance_percentage", "Demon_attack_chance_percentage", demon_attack_chance_percentage, i, Props["Demon_projectile_speed_in_pixels_per_second"]);

    // Mage Properties
	i = genertateFloatProperty("attack_texture_update_rate_per_second", "Attack_texture_update_rate_per_second", attack_texture_update_rate_per_second, i, Props["Demon_attack_chance_percentage"]);
	i = genertateFloatProperty("casting_shield_texutre_update_rate_per_second", "Casting_shield_texutre_update_rate_per_second", casting_shield_texutre_update_rate_per_second, i, Props["Attack_texture_update_rate_per_second"]);
	i = genertateFloatProperty("mage_speed_in_pixels_per_second", "Mage_speed_in_pixels_per_second", mage_speed_in_pixels_per_second, i, Props["Casting_shield_texutre_update_rate_per_second"]);
	i = genertateFloatProperty("mage_attack_rate_per_second", "Mage_attack_rate_per_second", mage_attack_rate_per_second, i, Props["Mage_speed_in_pixels_per_second"]);
	i = genertateFloatProperty("mage_projectile_speed_in_pixels_per_second", "Mage_projectile_speed_in_pixels_per_second", mage_projectile_speed_in_pixels_per_second, i, Props["Mage_attack_rate_per_second"]);

    count = i;
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

int Properties::genertateIntProperty(string document_key, string props_key, int default_value, int count, shared_ptr<Node<Property>> previous) {
    count++;
    int value;
	Properties_document.HasMember(document_key.c_str()) ? value = Properties_document[document_key.c_str()].GetInt() : value = default_value;

	shared_ptr<Property> prop = make_shared<Property>(props_key, value, count);
	Props[props_key] = make_shared<Node<Property>>(prop);
    assignPreviousandNext(previous, Props[props_key]);
    return count;
}

int Properties::genertateBoolProperty(string document_key, string props_key, bool default_value, int count, shared_ptr<Node<Property>> previous) {
    count++;
    bool value;
    Properties_document.HasMember(document_key.c_str()) ? value = Properties_document[document_key.c_str()].GetBool() : value = default_value;

    shared_ptr<Property> prop = make_shared<Property>(props_key, value, count);
    Props[props_key] = make_shared<Node<Property>>(prop);
    assignPreviousandNext(previous, Props[props_key]);
    return count;
}

int Properties::genertateFloatProperty(string document_key, string props_key, float default_value, int count, shared_ptr<Node<Property>> previous) {
    count++;
    float value;
    Properties_document.HasMember(document_key.c_str()) ? value = Properties_document[document_key.c_str()].GetFloat() : value = default_value;

    shared_ptr<Property> prop = make_shared<Property>(props_key, value, count);
    Props[props_key] = make_shared<Node<Property>>(prop);
    assignPreviousandNext(previous, Props[props_key]);
    return count;
}

int Properties::getCount() { return count; }
bool Properties::getBoolPropertyValue(string property) { return static_cast<bool>(Props[property]->Data->getValue()); }
int Properties::getIntPropertyValue(string property) { return static_cast<int>(Props[property]->Data->getValue()); }
float Properties::getFloatPropertyValue(string property) { return Props[property]->Data->getValue(); }

shared_ptr<Node<Property>> Properties::getPropertyByPosition(int property_position) {
	//for (auto& prop : Props) { // Provided by copilot. Concerned about the &
    for (auto& prop : Props) {
		//if (prop.second->Data->getLocation() == property_position) { return prop.second; } // Provided by copilot. Concerned about the &
        if (prop.second->Data->getLocation() == property_position) { return Props[prop.first]; }
	}
}

shared_ptr<Node<Property>> Properties::getPropertyByName(string property) { 
    if (Props.find(property) == Props.end()) { return nullptr; };
    return Props[property]; 
}




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

Property::Property(string key, float value, int location) : Key(key), Value(value), Location(location), IsFloat(true), IsBool(false) {}
Property::Property(string key, int value, int location) : Key(key), Value(static_cast<float>(value)), Location(location), IsFloat(false), IsBool(false) {}
Property::Property(string key, bool value, int location) : Key(key), Value(static_cast<float>(value)), Location(location), IsFloat(false), IsBool(true) {}
Property::Property(){}

void Property::setKey(string key) { Key = key; }
void Property::setValue(float value) { Value = value; }
void Property::setLocation(int location) { Location = location; }
string Property::getKey() { return Key; }
float Property::getValue(){ return Value; }
int Property::getLocation() { return Location; }
int Property::getPropertyWidth(int font_size) { return Key.length() * font_size * .65; }
bool Property::getIsFloat() { return IsFloat; }
bool Property::getIsBool() { return IsBool; }
