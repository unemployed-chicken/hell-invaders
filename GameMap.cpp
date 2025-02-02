#include "GameMap.h"

GameMap::GameMap(Texture2D background, Texture2D midground, Texture2D foreground)
	: Background(background), Midground(midground), Foreground(foreground){}

// per Chatgpt this is only necessary if we need to manage the individual pionter because std::vector manages this for us
//GameMap::~GameMap() {
//    for (Projectile* projectile : Active_projectiles) {
//        delete projectile;
//    }
//    Active_projectiles.clear();
//}


void GameMap::appendProjectile(Mage& mage) {
	mage.setIsProjectileReady(false);
	Active_projectiles.push_back( make_unique<Projectile>(
		mage.getProjectileTexture(), 4, 3, mage.getXCoordinate(), mage.getYCoordinate(), mage.getAttackDirection(), 
		mage_projectile_collision_offset_x, mage_projectile_collision_offset_y, mage_projectile_collision_scale_x,
		mage_projectile_collision_scale_y, mage_projectile_rotation, true));
}

void GameMap::tick(float dT, Mage &mage){
	drawBackground();

	if (mage.getIsProjectileReady()) {
		appendProjectile(mage);
	}

	if (!Active_projectiles.empty()) {
		int i = 0;
		// Working but is inefficient if there are a lot of projectiles.
		while (Active_projectiles.begin() + i != Active_projectiles.end()) {
			Active_projectiles[i]->tick(dT);
			if (Active_projectiles[i]->getYCoordinate() <= 0.0f || Active_projectiles[i]->getYCoordinate() >= window_dimensions[1]) {
				Active_projectiles.erase(Active_projectiles.begin() + i);
				std::cout << "ERASING! \n";
			}
			else {
				++i;
			}
		}
	}
}

void GameMap::drawBackground() {
	DrawTextureEx(Background, background_pos, 0.0, background_scale, WHITE);
	DrawTextureEx(Midground, midground_pos, 0.0, midground_scale, WHITE);
	DrawTextureEx(Foreground, foreground_pos, 0.0, foreground_scale, WHITE);
}

