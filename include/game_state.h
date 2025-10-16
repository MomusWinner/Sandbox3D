#pragma once

#include "raylib.h"
#include "world.h"

class GameState {
public:
    GameState(GameState &other) = delete;
	void operator=(const GameState&) = delete;
	
	static GameState& GetInstance() {
		static GameState instance;
		return instance;
	}

	Camera* camera;
	World* world;

private:
	GameState() {}
    static GameState* m_instance;
};
