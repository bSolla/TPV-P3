#pragma once
#include "GameStateMachine.h"
#include "GameState.h"
#include "MainMenu.h"
#include "PlayState.h"
#include "PauseMenu.h"
#include "Utilities.h"
#include "Texture.h"

class Game {
private:
	GameStateMachine *stateMachine = nullptr;
	bool exit = false;

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture* textures[NUM_TEXTURES];

	// initializes SDL 
	void iniSDL();
	// initializes all textures
	void iniTextures();

public:
	Game();
	~Game();

	GameStateMachine* getStateMachine () const { return stateMachine; }
	Texture* getTexture(TextureNames textureName) const { return textures[textureName]; }
	SDL_Renderer* getRenderer() const { return renderer; }

	void setExit (bool value) { exit = value; }
	void startGame ();
	void pauseMenu ();
	void backToGame () { getStateMachine ()->popState (); } //TODO: clean up
	void backToMainMenu () { backToGame (); getStateMachine ()->popState (); } // TODO: clean 

	void resizeWindow (int newHeight, int newWidth) { } //TODO: fill
	// renders the instructions screen for entering the file code for loading
	void renderInstructions ();
	// renders a number "keyboard" to use for entering the file code for loading
	void renderNumberButtons ();
	// returns true if the player clicked on one of the numbers or the "done" button, and returns a reference to said number (-1=done)
	bool handleNumberButtons (SDL_Event SDLevent, int &number);

	void loadFromFile (string code) { cout << "load file:" << code << "\n"; } // TODO: fill

	void handleEvents ();
	void run ();
	void render ();
	void update ();
};

