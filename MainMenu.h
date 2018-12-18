#pragma once
#include "MenuState.h"


class MainMenu : public MenuState {
private:
	static void play (Game *gamePtr);
	static void load (Game *gamePtr);

public:
	MainMenu ();
	~MainMenu ();
};

