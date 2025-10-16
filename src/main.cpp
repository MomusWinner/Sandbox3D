#include <string>

#include "block.h"
#include "physics.h"
#include "raylib.h"
#include "rlgl.h"
#include "rcamera.h"
#include "utils.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "external/glad.h"          // GLAD extensions loading library, includes OpenGL headers

#include "character_controller.h"
#include "game_state.h"
#include "resource_dir.h"
#include "world.h"

using namespace std;

const int screenWidth = 1280;
const int screenHeight = 800;

Physics* physics;
CharacterController* player;
World* world;
Camera* camera;

Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
Vector2 cubeScreenPosition = { 0.0f, 0.0f };

void Init();
void Update(float);
void Draw();
void Clean();

int main () {
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(screenWidth, screenHeight, "Sandbox");

	SearchAndSetResourceDir("resources");

	Init();

	while (!WindowShouldClose()) {
		Update(GetFrameTime());

		BeginDrawing();
		Draw();
		EndDrawing();
	}

	Clean();
	return 0;
}

void Init() {
	rlEnableBackfaceCulling();

	camera = new Camera {
		Vector3 { 10.0f, 10.0f, 10.0f }, // Camera position
		Vector3 { 0.0f, 0.0f, 0.0f },    // Camera looking at point
		Vector3 { 0.0f, 1.0f, 0.0f },    // Camera up vector (rotation towards target)
		45.0f,                           // Camera field-of-view Y
		CAMERA_PERSPECTIVE,              // Camera projection type
	};

	physics = new Physics();
	GameState::GetInstance().camera = camera;

	player = new CharacterController(5, 0.005f);
	player->position = Vector3 { 10.0f, 10.0f, 10.0f };
	player->init();

	world = new World();
	world->init();
	//create platform
	//world->createPlatform({0, 0, 0}, 196, 1, 196);
	world->createPlatform({0, 0, 0}, 10, 1, 10);
	//world->createPlatform(VectorToBlockPosition(HALF_BLOCK_SIZE_VECTOR * 50), 10, 10, 10);

	GameState::GetInstance().world = world;

    DisableCursor();
    SetTargetFPS(60); 
}

void Update(float dt) {
	physics->usePhysic(player, world->getBlocks(), dt);
	player->update(dt);
	world->update(dt);

}

void DrawProfile() {
	// DrawText("SandBox", 10, 10, 20, WHITE);
	// string fpsStr = "FPS: " + to_string(GetFPS());
	//
	// DrawText(fpsStr.c_str(), 10, 30, 20, WHITE);
}

void Draw() {
	ClearBackground(DARKBLUE);

	BeginMode3D(*camera);
		//DrawGrid(1000, 1.0f);
		world->draw();
		player->draw();
	EndMode3D();


	DrawProfile();
	DrawCircle(screenWidth / 2, screenHeight / 2, 1, WHITE);
}

void Clean() {
	CloseWindow();
}
