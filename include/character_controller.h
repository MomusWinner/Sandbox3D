#pragma once

#include "raylib.h"

class CharacterController {
public:
	Vector3 position;
	Vector3 velocity;

	CharacterController(float speed, float rotationSpeed);
	~CharacterController();

	void init();
	void update(float dt);
	void draw();
	void clear();

	BoundingBox getCollision();

private:
	Camera* m_camera;
	float m_speed;
	float m_rotationSpeed;
};
