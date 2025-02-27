#include "ReviveShield.h"

ReviveShield::ReviveShield(Texture2D revive_shield) : Shield(revive_shield, 300) {
	Is_persistent = true;
	Width_scale = 20;
	X_coordinate = 5;
}

