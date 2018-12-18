#pragma once
#include <iostream>
#include <fstream>
#include "GameObject.h"
#include "Vector2D.h"
#include "Texture.h"
#include "Utilities.h"
#include "FileFormatError.h"

class Game;

class SDLGameObject : public GameObject {
protected:
	Vector2D position;
	int width = STANDARD_CELL_WIDTH;
	int height = STANDARD_CELL_HEIGHT;

	Texture* texture = nullptr;
	Game* game = nullptr;

public:
	SDLGameObject() {};
	SDLGameObject(Game* gameptr, int posX, int posY, int width, int height, Texture* texture, TextureNames textureName);

	virtual ~SDLGameObject() {};

	virtual SDL_Rect getRect();

	virtual bool collides(SDL_Rect objectRect, Vector2D &collVector) { return false; };

	virtual void render();

	virtual void update() = 0;

	virtual bool handleEvents (SDL_Event &e) { return false; }
};