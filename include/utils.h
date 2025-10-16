#pragma once

#include "block.h"
#include <string>

inline std::string v_to_string(Vector3 v) {
    return "Vector3: " + std::to_string(v.x) + " | " + std::to_string(v.y) + " | " + std::to_string(v.z) + "";
}

inline std::string bp_to_string(BlockPosition v) {
    return "Vector3: " + std::to_string(v.x) + " | " + std::to_string(v.y) + " | " + std::to_string(v.z) + "";
}

inline BlockPosition VectorToBlockPosition(Vector3 vec) {
	return { int(vec.x), int(vec.y), int(vec.z) };
}
