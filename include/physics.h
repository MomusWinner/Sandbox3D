#pragma once

#include "block.h"
#include "character_controller.h"
#include <vector>

#define G_ACCELERATION 5 //9.8067

struct Collision {
	BoundingBox	box;
	Vector3 position;
};

class Physics {
public:
	void usePhysic(CharacterController* player, std::vector<Block*> blocks, float dt) {
		bool playerOnGround = false;

		// for (Block* block : blocks) {
		// 	BoundingBox blockCollision = {
		// 		block->position.toVector() - HALF_BLOCK_SIZE_VECTOR,
		// 		block->position.toVector() + HALF_BLOCK_SIZE_VECTOR,
		// 	};
		//
		// 	if (CheckCollisionBoxes(player->getCollision(), blockCollision)) {
		// 		playerOnGround = true;
		// 		break;
		// 	}
		// }
		//
		// if (!playerOnGround) {
		// 	player->position -= Vector3{0, G_ACCELERATION * dt,0};
		// }
		// else {
		// 	player->position += Vector3{0, 0.1f * dt , 0};
		// }
	}
};

