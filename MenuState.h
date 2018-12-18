#pragma once
#include "GameState.h"


class MenuState : public GameState {
protected:
	static void endGame (Game *gamePtr);

public:
	MenuState();
	~MenuState();
	
};

