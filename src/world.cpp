#include <utility>
#include <vector>
#include "world.h"
#include "block.h"
#include "game_state.h"
#include "raylib.h"
#include "raymath.h"
#include "utils.h"

void unhighlight(std::vector<Block*> blocks) {
	for (Block* block : blocks) {
		block->highlight = false;
	}
}

void World::init() {
	m_blockModel = LoadModel("block.obj");
}

void World::update(float dt) {

}

void World::draw() {
	for (Block* block : m_blocks) {
		DrawModel(m_blockModel, block->position.toVector(), HALF_BLOCK_SIZE, DARKGREEN);
		//DrawCubeV(block->position.toVector(), BLOCK_SIZE_VECTOR, DARKGREEN);
		// if (block->highlight) {
		// 	DrawCubeWiresV(block->position.toVector(), BLOCK_SIZE_VECTOR, RED);
		// }
		// else {
		//DrawCubeWiresV(block->position.toVector(), BLOCK_SIZE_VECTOR, GREEN);
		//}
	}
}

void World::addBlock(Block* block) {
	if (getBlock(block->position) != nullptr) {
		TraceLog(LOG_WARNING, "Block with same position already exist");
		return;
	}
	m_blocks.push_back(block);
}


Block* World::getBlock(BlockPosition pos) {
	for (Block* block : m_blocks) {
		if (block->position == pos) {
			return block;
		}
	}

	return nullptr;
}

std::vector<Block*> World::getBlocks() {
	return m_blocks;
}

void World::createPlatform(BlockPosition center, int width, int height, int length) {
	for (int x = 0; x < length; ++x) {
		for (int y = 0; y < height; ++y) {
			for (int z = 0; z < width; ++z) {
				int blockSize = BLOCK_SIZE;
				addBlock(new Block(BLOCK_SIZE * BlockPosition{center.x - x + int(length / 2), center.y - y + int(height/2), center.z - z + int(width/2)}));
			}
		}
	}
}

RayHit World::getCollision(Ray ray) {
	std::vector<std::pair<Block*, RayCollision>> hitedBlocks {};

	for (Block* block : m_blocks) {
		Vector3 min = block->position.toVector() - HALF_BLOCK_SIZE_VECTOR;
		Vector3 max = block->position.toVector() + HALF_BLOCK_SIZE_VECTOR;

		RayCollision col = GetRayCollisionBox(ray, BoundingBox { min, max });
		if (!col.hit) {
			continue;
		}
		hitedBlocks.push_back(std::make_pair(block, col));
	}

	TraceLog(LOG_INFO, ("Hited: " + std::to_string(hitedBlocks.size())).c_str());
	
	if (hitedBlocks.empty()) {
		return RayHit { false };
	}

	Block* nearestBlock = nullptr;
	RayCollision* rayCollision = nullptr;
	float minDist = MAXFLOAT;

	for (auto& [block, rCol] : hitedBlocks) {

		float dist = Vector3LengthSqr(block->position.toVector() - ray.position);
		if (dist < minDist) {
			minDist = dist;
			nearestBlock = block;
			rayCollision = &rCol;
		}
	}
	
	unhighlight(m_blocks);
	nearestBlock->highlight = true;

	Vector3 resultDir;

	std::string pointString = "Point: " + v_to_string(rayCollision->point);
	std::string blockString = "Block: " + nearestBlock->position.toString();

	TraceLog(LOG_INFO, pointString.c_str());
	TraceLog(LOG_INFO, blockString.c_str());

	Vector3 blocktoHit = rayCollision->point - nearestBlock->position.toVector();

	Vector3 direcctions[] {
		{ 0, 0, 1 },  // forward
		{ 0, 0, -1 }, // back
		{ 1, 0, 0 },  // right
		{ -1, 0, 0 }, // left
		{ 0, 1, 0 },  // up
		{ 0, -1, 0 }, // bottom
	};

	float minD = MAXFLOAT;

	for (Vector3 dir : direcctions) {
		float diff = Vector3LengthSqr(blocktoHit - dir);
		if (diff < minD) {
			resultDir = dir;
			minD = diff;
		}
	}

	TraceLog(LOG_INFO, ("CREATE DIR: " + v_to_string(resultDir)).c_str());

	return RayHit {
		true,
		resultDir,
		nearestBlock,
		VectorToBlockPosition(nearestBlock->position.toVector() + resultDir * BLOCK_SIZE_VECTOR),
	};
}
