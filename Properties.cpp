#include "Properties.h"


void Properties::assignPreviousandNext(shared_ptr<Node<Property>> previous, shared_ptr<Node<Property>> next) {
	if (previous) { previous->Next = next; }
	if (next) {	next->Previous = previous; }
}

void Properties::generateHighScores() {
    string path = base_path;
    path.append("props/high_scores.json");

    FILE* fp;
    fp = fopen(path.c_str(), "r"); // non-Windows use "r" 

    if (fp) {
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        High_scores.ParseStream(is);
        fclose(fp);
    }
    else {
        High_scores.SetObject();
    }

    if (High_scores.HasParseError() || !High_scores.IsObject()) {
        High_scores.SetObject();
    }
}


Properties::Properties() {
    generateHighScores();

    string path = base_path;
    path.append("props/user_defined_properties.json");

	rapidjson::Document properties_details = generatePropertyDescriptions();
	FILE* fp;
    fp = fopen(path.c_str(), "r"); // non-Windows use "r" 

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
        Properties_document.SetObject();
    }
    
    int i{ 0 };

    // General Game Properties
    i = generateIntProperty("number_of_starting_lives", "Number_of_starting_lives", number_of_starting_lives, i, nullptr, properties_details);
	i = generateIntProperty("number_of_starting_shields", "Number_of_starting_shields", number_of_starting_shields, i, Props["Number_of_starting_lives"], properties_details);
	i = generateIntProperty("number_of_texure_updates_rate_per_second", "Number_of_texure_updates_rate_per_second", number_of_texure_updates_rate_per_second, i, Props["Number_of_starting_shields"], properties_details);
	i = generateIntProperty("revive_shield_movement_speed_in_pixels_per_second", "Revive_shield_movement_speed_in_pixels_per_second", revive_shield_movement_speed_in_pixels_per_second, i, Props["Number_of_texure_updates_rate_per_second"], properties_details);
	i = generateBoolProperty("should_skip_intro", "Should_skip_intro", should_skip_intro, i, Props["Revive_shield_movement_speed_in_pixels_per_second"], properties_details);
	i = generateBoolProperty("should_start_with_shields_active", "Should_start_with_shields_active", should_start_with_shields_active, i, Props["Should_skip_intro"], properties_details);
	i = generateBoolProperty("should_projectiles_collide", "Should_projectiles_collide", should_projectiles_collide, i, Props["Should_start_with_shields_active"], properties_details);
	i = generateBoolProperty("is_music_on", "Is_music_on", is_music_on, i, Props["Should_projectiles_collide"], properties_details);
    i = generateIntProperty("music_volume", "Music_volume", music_volume, i, Props["Is_music_on"], properties_details);

	// Demon Properties
	i = generateIntProperty("number_of_demon_columns", "Number_of_demon_columns", number_of_demon_columns, i, Props["Music_volume"], properties_details);
	i = generateIntProperty("number_of_rows_before_speed_boost", "Number_of_rows_before_speed_boost", number_of_rows_before_speed_boost, i, Props["Number_of_demon_columns"], properties_details);
	i = generateIntProperty("demon_base_points", "Demon_base_points", demon_base_points, i, Props["Number_of_rows_before_speed_boost"], properties_details);
	i = generateIntProperty("scamp_score_multiplier", "Scamp_score_multiplier", scamp_score_multiplier, i, Props["Demon_base_points"], properties_details);
	i = generateIntProperty("fledgling_score_multiplier", "Fledgling_score_multiplier", fledgling_score_multiplier, i, Props["Scamp_score_multiplier"], properties_details);
	i = generateIntProperty("skull_score_multiplier", "Skull_score_multiplier", skull_score_multiplier, i, Props["Fledgling_score_multiplier"], properties_details);
	i = generateIntProperty("eye_score_multipler", "Eye_score_multipler", eye_score_multipler, i, Props["Skull_score_multiplier"], properties_details);

    // Demon Mechanic Properties
	i = generateIntProperty("demon_base_speed_in_pixels_per_second", "Demon_base_speed_in_pixels_per_second", demon_base_speed_in_pixels_per_second, i, Props["Eye_score_multipler"], properties_details);
	i = generateIntProperty("demon_acceleration_in_pixels_per_second", "Demon_acceleration_in_pixels_per_second", demon_acceleration_in_pixels_per_second, i, Props["Demon_base_speed_in_pixels_per_second"], properties_details);
	i = generateIntProperty("demon_level_acceleration_in_pixels_per_second", "Demon_level_acceleration_in_pixels_per_second", demon_level_acceleration_in_pixels_per_second, i, Props["Demon_acceleration_in_pixels_per_second"], properties_details);
	i = generateIntProperty("demon_projectile_speed_in_pixels_per_second", "Demon_projectile_speed_in_pixels_per_second", demon_projectile_speed_in_pixels_per_second, i, Props["Demon_level_acceleration_in_pixels_per_second"], properties_details);
    i = generateIntProperty("demon_attack_rate_in_milliseconds", "Demon_attack_rate_in_milliseconds", demon_attack_rate_in_milliseconds, i, Props["Demon_projectile_speed_in_pixels_per_second"], properties_details);
    i = generateIntProperty("demon_attack_chance_percentage", "Demon_attack_chance_percentage", demon_attack_chance_percentage, i, Props["Demon_attack_rate_in_milliseconds"], properties_details);

    // Mage Properties
	i = generateIntProperty("attack_texture_update_rate_per_second", "Attack_texture_update_rate_per_second", attack_texture_update_rate_per_second, i, Props["Demon_attack_chance_percentage"], properties_details);
	i = generateIntProperty("casting_shield_texture_update_rate_per_second", "Casting_shield_texture_update_rate_per_second", casting_shield_texture_update_rate_per_second, i, Props["Attack_texture_update_rate_per_second"], properties_details);
	i = generateIntProperty("mage_speed_in_pixels_per_second", "Mage_speed_in_pixels_per_second", mage_speed_in_pixels_per_second, i, Props["Casting_shield_texture_update_rate_per_second"], properties_details);
	i = generateIntProperty("mage_attack_rate_in_millisecond", "Mage_attack_rate_in_millisecond", mage_attack_rate_in_millisecond, i, Props["Mage_speed_in_pixels_per_second"], properties_details);
	i = generateIntProperty("mage_projectile_speed_in_pixels_per_second", "Mage_projectile_speed_in_pixels_per_second", mage_projectile_speed_in_pixels_per_second, i, Props["Mage_attack_rate_in_millisecond"], properties_details);

    count = i;
}

void Properties::saveScores() {
    string path = base_path;
    path.append("props/high_scores.json");

    FILE* fp;
    fp = fopen(path.c_str(), "w"); // non-Windows use "w" 

    if (fp) {
        char writeBuffer[65536];
        rapidjson::FileWriteStream os(fp, writeBuffer,
            sizeof(writeBuffer));
        rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
        High_scores.Accept(writer);
        fclose(fp);
    }
}

void Properties::saveProperties() {
    string path = base_path;
    path.append("props/user_defined_properties.json");

    FILE* fp;
    fp = fopen(path.c_str(), "w"); // non-Windows use "w" 

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
    Properties_document.SetObject();
    saveProperties();
}

void Properties::updateIntProperty(string key, int value) {
    std::transform(key.begin(), key.begin()+1, key.begin(), ::tolower);
    if (Properties_document.HasMember(key.c_str())) {
        rapidjson::Value& property = Properties_document[key.c_str()];
        property.SetInt(value);
    }
    else {
        rapidjson::Value v_key;
        v_key.SetString(key.c_str(), Properties_document.GetAllocator());
        rapidjson::Value v_value(value); 
        Properties_document.AddMember(v_key, v_value, Properties_document.GetAllocator());
    }
}

void Properties::updateBoolProperty(string key, bool value) {
    std::transform(key.begin(), key.begin() + 1, key.begin(), ::tolower);
    if (Properties_document.HasMember(key.c_str())) {
        rapidjson::Value& property = Properties_document[key.c_str()];
        property.SetInt(value);
    }
    else {
        rapidjson::Value v_key;
        v_key.SetString(key.c_str(), Properties_document.GetAllocator());
        rapidjson::Value v_value{};
        v_value.SetInt(static_cast<int>(value));
        Properties_document.AddMember(v_key, v_value, Properties_document.GetAllocator());
    }
}

void Properties::updateFloatProperty(string key, float value) {
    std::transform(key.begin(), key.begin() + 1, key.begin(), ::tolower);
    if (Properties_document.HasMember(key.c_str())) {
        rapidjson::Value& property = Properties_document[key.c_str()];
        property.SetFloat(value);
    }
    else {
        rapidjson::Value v_key;
        v_key.SetString(key.c_str(), Properties_document.GetAllocator());
        rapidjson::Value v_value{};
		v_value.SetFloat(value);
        Properties_document.AddMember(v_key, v_value, Properties_document.GetAllocator());
    }
}

void Properties::setScore(pair<string, int> score, const string position) { 
    // Possibly rapidjson::MemoryPoolAllocator
    auto& allocator = High_scores.GetAllocator();
    rapidjson::Value& score_entry = High_scores[position.c_str()];

    rapidjson::Value initials;
    initials.SetString(score.first.c_str(), static_cast<rapidjson::SizeType>(score.first.length()), allocator);
    score_entry["initials"] = initials;
    score_entry["score"].SetInt(score.second);
}

int Properties::generateIntProperty(string document_key, string props_key, int default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details) {
    count++;
    int value;
	
    Properties_document.HasMember(document_key.c_str()) ? value = Properties_document[document_key.c_str()].GetInt() : value = default_value;

	shared_ptr<Property> prop = make_shared<Property>(props_key, value, count, default_value, properties_details);
	Props[props_key] = make_shared<Node<Property>>(prop);
    assignPreviousandNext(previous, Props[props_key]);
    return count;
}

int Properties::generateBoolProperty(string document_key, string props_key, bool default_value, int count, shared_ptr<Node<Property>> previous, rapidjson::Document& properties_details) {
    count++;
    bool value;

    Properties_document.HasMember(document_key.c_str()) ? value = Properties_document[document_key.c_str()].GetInt() : value = default_value;

    shared_ptr<Property> prop = make_shared<Property>(props_key, value, count, default_value, properties_details);
    Props[props_key] = make_shared<Node<Property>>(prop);
    assignPreviousandNext(previous, Props[props_key]);
    return count;
}


int Properties::getCount() { return count; }
bool Properties::getBoolPropertyValue(const string property) { return static_cast<bool>(Props[property]->Data->getValue()); }
int Properties::getIntPropertyValue(const string property) { return static_cast<int>(Props[property]->Data->getValue()); }
float Properties::getFloatPropertyValue(const string property) { return Props[property]->Data->getValue(); }
float Properties::getPerSecondPropertyValue(const string property) { return 1.0 / Props[property]->Data->getValue(); }

pair<string, int> Properties::getScore(const string position) { 
    string initials;
    int score;

    if (High_scores.HasMember(position.c_str())) {
        initials = High_scores[position.c_str()]["initials"].GetString();
        score = High_scores[position.c_str()]["score"].GetInt();
    }
    return std::pair<string, int>(initials, score);
}

shared_ptr<Node<Property>> Properties::getPropertyByPosition(int property_position) {
    for (auto prop : Props) {
        if (prop.second->Data->getLocation() == property_position) { return Props[prop.first]; }
	}
}

shared_ptr<Node<Property>> Properties::getPropertyByName(string property) { 
    if (Props.find(property) == Props.end()) { return nullptr; };
    return Props[property]; 
}

rapidjson::Document Properties::generatePropertyDescriptions() {
    rapidjson::Document properties_details_document;

    string path = base_path;
    path.append("props/properties_details.json");

    FILE* fp;
    fp = fopen(path.c_str(), "r"); // non-Windows use "r" 

    if (fp) {
        char readBuffer[65536];
        rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
        properties_details_document.ParseStream(is);
        fclose(fp);
    }
    else {
        properties_details_document.SetObject();
    }

    if (properties_details_document.HasParseError() || !properties_details_document.IsObject()) {
        properties_details_document.SetObject();
    }

    return properties_details_document;
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

void Property::assignDetails(rapidjson::Document& details, string key) {
    std::transform(key.begin(), key.begin() + 1, key.begin(), ::tolower);

    if (details.HasMember(key.c_str())) {
        Name = details[key.c_str()]["name"].GetString();
        Description = details[key.c_str()]["description"].GetString();
        Increment_counter = details[key.c_str()]["increment"].GetInt();
        Max_value = details[key.c_str()]["max"].GetInt();
        Min_value = details[key.c_str()]["min"].GetInt();
    }
}

Property::Property(string key, float value, int location, float default_value, rapidjson::Document& details) : Key(key), Value(value), Location(location), IsFloat(true), IsBool(false), Default_value(default_value) {
    assignDetails(details, key);
}
Property::Property(string key, int value, int location, int default_value, rapidjson::Document& details) : Key(key), Value(static_cast<float>(value)), Location(location), IsFloat(false), IsBool(false), Default_value(static_cast<float>(default_value)) {
    assignDetails(details, key);
}
Property::Property(string key, bool value, int location, bool default_value, rapidjson::Document& details) : Key(key), Value(static_cast<float>(value)), Location(location), IsFloat(false), IsBool(true), Default_value(static_cast<float>(default_value)) {
	assignDetails(details, key);
}
Property::Property(){}

void Property::setKey(string key) { Key = key; }
void Property::setValue(float value) { Value = value; }
void Property::setLocation(int location) { Location = location; }
void Property::incrementValue(int direction) {
    if (IsBool) {
        if (Value == 0) { Value = 1; }
        else { Value = 0; }
	}
    else {
        if (Value + Increment_counter * direction >= Min_value && Value + Increment_counter * direction <= Max_value ) { Value += Increment_counter * direction; }
    }
} 

string Property::getKey() { return Key; }
float Property::getValue(){ return Value; }
int Property::getLocation() { return Location; }
bool Property::getIsFloat() { return IsFloat; }
bool Property::getIsBool() { return IsBool; }

int Property::getMinValue() { return Min_value; }
int Property::getMaxValue() { return Max_value; }
int Property::getDefaultValue() { return Default_value; }

string Property::getDescription(){ return Description; }
string Property::getName() { return Name; }
int Property::getIncrementCounter() { return Increment_counter; }
