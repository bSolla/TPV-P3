#pragma once
#include "MenuState.h"


using namespace std;


class MainMenu : public MenuState {
private:
	enum ButtonTypes { Play, Load, Exit };
	const Vector2D buttonPositions[3] = { {double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 2)}, 
									{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 4)}, 
									{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 6)} };



	static void play (Game *gamePtr);
	static void load (Game *gamePtr);


public:
	MainMenu (Game *gamePtr);
	~MainMenu ();

	virtual void render () { MenuState::render (); }
	virtual void update () { MenuState::update (); }
	virtual bool handleEvents (SDL_Event &e) { return MenuState::handleEvents (e); }
};

