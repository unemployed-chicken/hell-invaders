#include "GameMap.h"

GameMap::GameMap(Texture2D background, Texture2D midground, Texture2D foreground)
	: Background(background), Midground(midground), Foreground(foreground){}

// per Chatgpt this is only necessary if we need to manage the individual pionter because std::vector manages this for us
//GameMap::~GameMap() {
//    for (Projectile* projectile : Active_projectiles) { // No longer using vector Active_projectiles
//        delete projectile;
//    }
//    Active_projectiles.clear(); // No longer using vector Active_projectiles
//}


void GameMap::appendProjectile(Mage& mage) {
	mage.setIsProjectileReady(false);
	Projectiles.insertAtEnd(make_shared<Node<Projectile>>(
		Projectile( mage.getProjectileTexture(), 4, 3, mage.getXCoordinate(), mage.getYCoordinate(),
			mage.getAttackDirection(),		mage_projectile_collision_offset_x, mage_projectile_collision_offset_y, 
			mage_projectile_collision_scale_x,		mage_projectile_collision_scale_y, mage_projectile_rotation, true
		)
	));
}

void GameMap::tick(float dT, Mage &mage){
	drawBackground();

	if (mage.getIsProjectileReady()) {
		appendProjectile(mage);
	}

	if (Projectiles.getCount() > 0) {
		shared_ptr<Node<Projectile>> current_node = Projectiles.getHead();
		while (current_node) {
			if (current_node->Data.getIsActive()) {
				current_node->Data.tick(dT);

				if (current_node->Data.getYCoordinate() <= 0.0f || current_node->Data.getYCoordinate() >= window_dimensions[1]) {
					current_node->Data.setIsActive(false);
				}
				current_node = current_node->Next; // We render in Tick function so doing this all in one line is not an issue.
			}

			else if (current_node == Projectiles.getHead()) {
				current_node = current_node->Next;
				Projectiles.deleteHead();
			}
			else if (current_node == Projectiles.getTail()) {
				current_node = current_node->Next;
				Projectiles.deleteTail();
			}
			else {
				current_node = current_node->Next;
				Projectiles.popNode(current_node->Previous);
			}
		}
	}
}

void GameMap::drawBackground() {
	DrawTextureEx(Background, background_pos, 0.0, background_scale, WHITE);
	DrawTextureEx(Midground, midground_pos, 0.0, midground_scale, WHITE);
	DrawTextureEx(Foreground, foreground_pos, 0.0, foreground_scale, WHITE);
}

