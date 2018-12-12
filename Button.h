#pragma once
#include "SDLGameObject.h"
class Button :
	public SDLGameObject
{
public:
	Button();
	~Button();

	// callbacks

	bool handleEvent(SDL_Event &e);
};

