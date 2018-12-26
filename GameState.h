#pragma once

#include <iostream>
#include <fstream>
#include <new>
#include <string>
#include <list>

#include "Utilities.h"
#include "SDLGameObject.h"
#include "Texture.h"
#include "Button.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "SDLError.h"
#include "ArkanoidError.h"

class Game;

typedef list<SDLGameObject*>::iterator itStage;

class GameState {
protected:
	list <SDLGameObject*> stage;
	Game* game;
	
public:
	virtual ~GameState();

	virtual void render();
	virtual void update();
	virtual bool handleEvents(SDL_Event &e); // be careful with self destruction here
};

