#include "GameState.h"
#include "Game.h"


GameState::~GameState(){
	for (itStage it = stage.begin(); it != stage.end(); it++)
		delete (*it);
}


void GameState::render() {
	for (auto it = stage.begin (); it != stage.end (); ++it) {
		(*it)->render ();
	}
}


void GameState::update(){
	auto it = stage.begin ();

	while (it != stage.end ()) {
		auto next = it;
		++next;
		(*it)->update ();
		it = next;
	}
}


bool GameState::handleEvents(SDL_Event &e) {
	auto it = stage.begin ();
	bool handled = false;

	while (it != stage.end () && !handled) {
		if ((*it)->handleEvents (e)) {
			handled = true;
		}
		else
			++it;
	}

	return handled;
}

