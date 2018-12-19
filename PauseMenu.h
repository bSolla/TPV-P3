#pragma once
#include "MenuState.h"


using namespace std;

class PauseMenu : public MenuState {
private:
	enum ButtonTypes { Play, Save, BackToMainMenu, Exit };
	const Vector2D buttonPositions[4] = { {double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8))}, 
									{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 3)}, 
									{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 5)}, 
									{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 7)} };


	static void resume (Game *gamePtr);
	static void save (Game *gamePtr);
	static void backToMainMenu (Game *gamePtr);

public:
	PauseMenu (Game *gamePtr);
	~PauseMenu ();

	virtual void render () { MenuState::render (); }

	virtual void update () { MenuState::render (); }

	virtual bool handleEvents (SDL_Event &e) { return MenuState::handleEvents (e); }
	
};

