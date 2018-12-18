#pragma once
#include "SDLGameObject.h"

class Game;

using CallBackOnClick = void (Game *gamePtr);


class Button : public SDLGameObject {
protected:
	CallBackOnClick *callback = nullptr;

public:
	Button(Game *gamePtr, Vector2D pos, CallBackOnClick cb);
	~Button();

	// callbacks

	bool handleEvent(SDL_Event &e);
};

