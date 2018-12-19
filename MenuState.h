#pragma once
#include "GameState.h"


class MenuState : public GameState {
protected:
	static void endGame (Game *gamePtr);

public:
	MenuState();
	~MenuState();
	
	virtual void render () { GameState::render (); }
	virtual void update () { GameState::update (); }
	virtual bool handleEvents (SDL_Event &e) { return GameState::handleEvents (e); }
};

