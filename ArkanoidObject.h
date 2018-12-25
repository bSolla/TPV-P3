#pragma once
#include "SDLGameObject.h"

class PlayState;

class ArkanoidObject : public SDLGameObject {
protected:
	PlayState *playState = nullptr;
public:
	ArkanoidObject();
	~ArkanoidObject();

	virtual bool collides (SDL_Rect objectRect, Vector2D &collVector) { return false; };

	virtual void loadFromFile(ifstream &file);

	virtual void saveToFile(ofstream &file);
};

