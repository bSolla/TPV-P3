#pragma once
#include "MenuState.h"
class PauseMenu : public MenuState {
private:
	static void resume (Game *gamePtr);
	static void save (Game *gamePtr);
	static void backToMainMenu (Game *gamePtr);

public:
	PauseMenu ();
	~PauseMenu ();

	
};

