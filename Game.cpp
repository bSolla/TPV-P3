#include "Game.h"


Game::Game() {
	
}


Game::~Game() {
}


void Game::handleEvents () {
	SDL_Event ev;  

	if (SDL_PollEvent (&ev)) {
		if (ev.type == SDL_QUIT) {
			exit = true;
		}
		else {
			stateMachine->currentState ()->handleEvents (ev);
		}
	}
}


void Game::run () {
	while (!exit) {
		stateMachine->currentState ()->update ();
		handleEvents ();
	}
}


void Game::render () {
	SDL_RenderClear (renderer);

	stateMachine->currentState ()->render ();

	SDL_RenderPresent (renderer);
}


void Game::update () {
	stateMachine->currentState ()->update ();

	handleEvents ();
	// handleTime ();
}
