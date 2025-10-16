#include "character_controller.h"
#include "block.h"
#include "game_state.h"
#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "world.h"

CharacterController::CharacterController(float speed, float rotationSpeed) {
	m_speed = speed;
	m_rotationSpeed = rotationSpeed;
	m_camera = GameState::GetInstance().camera;
}

void CharacterController::init() {
	m_camera->position = position;
}

void CharacterController::update(float dt) {
	m_camera->position = position;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Ray ray = Ray {
			m_camera->position,
			GetCameraForward(m_camera)
		};

		World* world = GameState::GetInstance().world;
		RayHit hit =  world->getCollision(ray);
		if (hit.isHit) {
			Block* block = new Block();
			block->position = hit.newBlockPos;
			world->addBlock(block);
		}
	}

	Vector2 mouseDelta = GetMouseDelta();
	CameraYaw(m_camera, -mouseDelta.x*m_rotationSpeed, false);
	CameraPitch(m_camera, -mouseDelta.y*m_rotationSpeed, false, false, false);


	Vector3 moveDirection = Vector3();
	float speedMultiply = 1;

	if (IsKeyDown(KEY_LEFT_SHIFT)) {
		speedMultiply = 3;
	}

	if (IsKeyDown(KEY_W)) {
		CameraMoveForward(m_camera, speedMultiply * m_speed * dt, false);

		// Vector3 forward = GetCameraForward(m_camera);
		//
		// // Project vector onto world plane
		// forward.y = 0;
		// forward = Vector3Normalize(forward);
		//
		// velocity += forward;

		// Scale by distance
		//forward = Vector3Scale(forward, distance);

		// Move position and target
		// camera->position = Vector3Add(camera->position, forward);
		// camera->target = Vector3Add(camera->target, forward);
	}
	// if (IsKeyDown(KEY_S)) {
	// 	CameraMoveForward(m_camera, -speedMultiply * m_speed * dt, false);
	// }
	// if (IsKeyDown(KEY_A)) {
	// 	CameraMoveRight(m_camera, -speedMultiply * m_speed * dt, false);
	// }
	// if (IsKeyDown(KEY_D)) {
	// 	CameraMoveRight(m_camera, speedMultiply * m_speed * dt, false);
	// }
	// if (IsKeyDown(KEY_SPACE)) {
	// 	CameraMoveUp(m_camera, speedMultiply * m_speed * dt);
	// }
	//
	
	// position += velocity;
	// m_camera->position = position;
	// m_camera->target += velocity;
	// position = m_camera->position;
	// velocity = Vector3Zero();
}

BoundingBox CharacterController::getCollision() {
	return {
		position + Vector3{ -1, -1, -1 },
		position + Vector3{ 1, 1, 1 },
	};
}

void CharacterController::draw() {
	Ray ray = Ray {
		m_camera->position,
		GetCameraForward(m_camera)
	};
	ray.position.y += 0.1;
	ray.position.x += 0.1;
	DrawRay(ray, BLACK);
}
