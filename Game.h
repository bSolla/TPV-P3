#pragma once
#include "GameStateMachine.h"
#include "GameState.h"
#include "MainMenu.h"
#include "PlayState.h"
#include "PauseMenu.h"
#include "Utilities.h"
#include "Texture.h"

class Game {
// --------------------- variables------------------------------------------------------
private:
	GameStateMachine *stateMachine = nullptr;
	bool exit = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture* textures[NUM_TEXTURES];


// ---------------------- methods ------------------------------------------------------
private:
	// initializes SDL 
	void iniSDL();
	// initializes all textures
	void iniTextures();

public:
	Game();
	~Game();

	// setters
	void setWindowSize (uint w, uint h) { SDL_SetWindowSize (window, w, h); }

	// getters
	GameStateMachine* getStateMachine () const { return stateMachine; }
	Texture* getTexture(TextureNames textureName) const { return textures[textureName]; }
	SDL_Renderer* getRenderer() const { return renderer; }

	// menu handling operations
	void setExit (bool value) { exit = value; }
	void startGame ();
	void pauseMenu ();
	void backToGame ();
	void backToMainMenu (); 

	void resizeWindow (int newHeight, int newWidth) { } //TODO: fill -- call this when entering/exiting a menu state
	// renders the instructions screen for entering the file code for loading
	void renderInstructions ();
	// renders a number "keyboard" to use for entering the file code for loading
	void renderNumberButtons ();
	// returns true if the player clicked on one of the numbers or the "done" button, and returns a reference to said number (-1=done)
	bool handleNumberButtons (SDL_Event SDLevent, int &number);

	void loadFromFile (string code) { cout << "load file:" << code << "\n"; } // TODO: fill --call loadFromFile of all the stage objects

	void handleEvents ();
	void run ();
	void render ();
	void update ();
};

