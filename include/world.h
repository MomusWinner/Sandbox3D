#pragma once

#include <vector>
#include "block.h"


struct RayHit {
	bool isHit;
	Vector3 side;
	Block* hitedBlock;
	BlockPosition newBlockPos;
};

class World{
public:
	World() = default;
	~World() = default;

	void init();
	void update(float dt);
	void draw();
	void clear();

	RayHit getCollision(Ray ray);
	std::vector<Block*> getBlocks();
	Block* getBlock(BlockPosition pos);

	void addBlock(Block* block);
	void createPlatform(BlockPosition center, int width, int height, int lenght);

private:
	std::vector<Block*> m_blocks;
	Model m_blockModel;

	void gravity();
};


// struct Vector3Comparator {
//     bool operator()(const Vector3& a, const Vector3& b) const {
//         return std::tie(a.x, a.y, a.z) < std::tie(b.x, b.y, b.z);
//     }
// };

//std::map<Vector3, std::unique_ptr<Block>> m_blocks;
