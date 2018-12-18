#pragma once
#include "GameStateMachine.h"
#include "GameState.h"
#include "Utilities.h"
#include "Texture.h"

class Game {
private:
	GameStateMachine *stateMachine = nullptr;
	bool exit = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture* textures[NUM_TEXTURES];

public:
	Game();
	~Game();

	GameStateMachine* getStateMachine () const { return stateMachine; }

	void handleEvents ();
	void run ();
	void render ();
	void update ();
};

