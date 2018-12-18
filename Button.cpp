#include "Button.h"



Button::Button(Game *gamePtr, Vector2D pos, CallBackOnClick cb) {
	double x = pos.getX ();
	double y = pos.getY ();

	game = gamePtr;
	position.setX (x);
	position.setY (y);
	callback = cb;
}


Button::~Button() {
	
}

bool Button::handleEvent(SDL_Event &e) {
	int mouseX, mouseY;
	bool click = false;

	if (e.type == SDL_MOUSEBUTTONUP) {
		SDL_GetMouseState (&mouseX, &mouseY);

		if (mouseX > int (position.getX ()) &&
			mouseX < int (position.getX () + width) &&
			mouseY > int (position.getY ()) &&
			mouseY < int (position.getY () + height)) {
			click = true;
			callback (game);
		}
	}

	return click;
}
