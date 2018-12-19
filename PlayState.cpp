#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(Game *gamePtr) {
	game = gamePtr;

	// create game objects
	// push them to the stage
	// possibly modify their constructors so they take their textures as attributes?? 
	// or do they need pointers to PlayState too??
}


PlayState::~PlayState() {
	// call parent destructor? or is it automatic?
}

void PlayState::render() {
	GameState::render ();

	//infoBar->render (seconds, minutes, currentLevel, lives);
}

void PlayState::update () {
	cout << "updating playScene\n";
	GameState::update ();
}

bool PlayState::handleEvents (SDL_Event & e) {
	bool handled = false;

	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			game->pauseMenu ();
			handled = true;
		}
	}


	return handled;
}
