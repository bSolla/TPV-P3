#include "GameState.h"
#include "Game.h"


GameState::~GameState(){
	for (itStage it = stage.begin(); it != stage.end(); it++)
		delete (*it);
}


void GameState::render() {
	for (itStage it = stage.begin (); it != stage.end (); ++it) {
		(*it)->render ();
	}
}


void GameState::update(){
	itStage it = stage.begin ();

	while (it != stage.end ()) {
		itStage next = it;
		++next;
		(*it)->update ();
		it = next;
	}
}


bool GameState::handleEvents(SDL_Event &e) {
	itStage it = stage.begin ();
	bool handled = false;

	while (!handled && it != stage.end ()) {
		if ((*it)->handleEvents (e)) {
			handled = true;
		}
		else
			++it;
	}

	return handled;
}

