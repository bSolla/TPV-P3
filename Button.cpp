#include "Button.h"



Button::Button(Game *gamePtr, Vector2D pos, CallBackOnClick cb, Texture *text, uint r) {
	double x = pos.getX ();
	double y = pos.getY ();

	game = gamePtr;
	position.setX (x);
	position.setY (y);
	callback = cb;
	texture = text;

	width = STANDARD_BUTTON_WIDTH;
	height = STANDARD_BUTTON_HEIGHT;

	row = r;
}


Button::~Button() {
	game = nullptr;
}

bool Button::handleEvents(SDL_Event &e) {
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

void Button::render () {
	texture->renderFrame (getRect (), row, col);
}
