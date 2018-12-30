#pragma once
#include "MenuState.h"

// TODO: use ttf to write "you win" or "you lose"
class EndMenu : public MenuState {
private:
	enum ButtonTypes { BackToMainMenu, Exit };
	const Vector2D buttonPositions[2] = { {double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 3)}, 
										{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 5)} };

	bool win;

	static void backToMainMenu (Game *gamePtr);

public:
	EndMenu (Game *gamePtr, bool won);
	~EndMenu ();

	
	virtual void render () { MenuState::render (); }

	virtual void update () { MenuState::render (); }

	virtual bool handleEvents (SDL_Event &e) { return MenuState::handleEvents (e); }
};

