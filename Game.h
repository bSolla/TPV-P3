#pragma once
#include "GameStateMachine.h"
#include "GameState.h"
#include "MainMenu.h"
#include "PlayState.h"
#include "PauseMenu.h"
#include "Utilities.h"
#include "Texture.h"
#include "EndMenu.h"

class Game {
// --------------------- variables------------------------------------------------------
private:
	GameStateMachine *stateMachine = nullptr;
	bool exit = false; // to exit and end the game

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	Texture* textures[NUM_TEXTURES];


// ---------------------- methods ------------------------------------------------------
private:
	// initializes SDL 
	void iniSDL();
	// initializes all textures
	void iniTextures();
	// pauses the game and saves numeric keyboard input as the file name
	string pickFileName ();
	// destroys both renderer and window and quits SDL
	void quitSDL();

public:
	Game();
	~Game();

	// setters
	void setWindowSize (uint w, uint h) { SDL_SetWindowSize (window, w, h); }
	void setExit (bool value) { exit = value; }
	
	// getters
	GameStateMachine* getStateMachine () const { return stateMachine; }
	Texture* getTexture(TextureNames textureName) const { return textures[textureName]; }
	SDL_Renderer* getRenderer() const { return renderer; }

	// menu handling operations
	void startGame ();
	void pauseMenu ();
	void endMenu (bool wonGame);
	// pops 1 time, used in the pause menu
	void backToGame ();
	// pops 2 times: used in the pause and end menu
	void backToMainMenu (); 

	// renders the instructions screen for entering the file code for loading
	void renderInstructions ();
	// renders a number "keyboard" to use for entering the file code for loading
	void renderNumberButtons ();
	// returns true if the player clicked on one of the numbers or the "done" button, and returns a reference to said number (-1=done)
	bool handleNumberButtons (SDL_Event SDLevent, int &number);
	// if it exists, loads the file with the code given
	void loadFromFile (string code); 
	// gets a code by cin and saves the current state on the game in file "code.ark"
	void saveToFile();

	void handleEvents ();
	void run ();
	void render ();
	void update ();
};

