#pragma once

#include "raylib.h"
#include <string>

constexpr int BLOCK_SIZE = 2;
constexpr int HALF_BLOCK_SIZE = BLOCK_SIZE / 2;
constexpr Vector3 BLOCK_SIZE_VECTOR = {BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
constexpr Vector3 HALF_BLOCK_SIZE_VECTOR = {HALF_BLOCK_SIZE, HALF_BLOCK_SIZE, HALF_BLOCK_SIZE};


struct BlockPosition {
	int x;
	int y;
	int z;

	Vector3 toVector() {
		return { float(x), float(y), float(z) };
	}

	std::string toString() {
    	return "BlockPos: " + std::to_string(x) + " | " + std::to_string(y) + " | " + std::to_string(z) + "";
	}
};

inline bool operator == (const BlockPosition& lhs, const BlockPosition& rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

inline BlockPosition operator + (const BlockPosition& lhs, const BlockPosition& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

inline BlockPosition operator * (int value, const BlockPosition& pos) {
	return { pos.x * value, pos.y * value, pos.z * value };
}

struct Block {
	Block(BlockPosition position) : position(position) {} 
	Block() : position(BlockPosition { 0, 0, 0 }) {}

	BlockPosition position;
	bool highlight;
};
