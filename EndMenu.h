#pragma once
#include "MenuState.h"


class EndMenu : public MenuState {
private:
	enum ButtonTypes { BackToMainMenu, Exit };
	const Vector2D buttonPositions[2] = { {double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 3)}, 
										{double(STANDARD_BUTTON_X), double((WIN_HEIGHT / 8) * 5)} };

	bool win;
	int row = 0; // determines if we use the win or you lost background 
	Texture *background = nullptr;

	static void backToMainMenu (Game *gamePtr);

public:
	EndMenu (Game *gamePtr, bool won);
	~EndMenu ();

	
	virtual void render ();

	virtual void update () { MenuState::render (); }

	virtual bool handleEvents (SDL_Event &e) { return MenuState::handleEvents (e); }
};

