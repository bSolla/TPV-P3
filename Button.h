#pragma once
#include "SDLGameObject.h"

class Game;

using CallBackOnClick = void (Game *gamePtr);

class Button : public SDLGameObject {
protected:
	CallBackOnClick *callback = nullptr;
	uint row = 0, col = 0;

public:
	Button(Game *gamePtr, Vector2D pos, CallBackOnClick cb, Texture *text, uint r);
	~Button();

	virtual bool handleEvents(SDL_Event &e);

	void update () {}
	void render ();
};

