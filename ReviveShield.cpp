#include "ReviveShield.h"

ReviveShield::ReviveShield(Texture2D revive_shield, Properties& properties) : Shield(revive_shield, 300) {
	Is_persistent = true;
	Width_scale = 20;
	X_coordinate = 5;
	Revive_shield_movement_speed = properties.getReviveShieldMovementSpeedInPixelsPerSecond();
}
