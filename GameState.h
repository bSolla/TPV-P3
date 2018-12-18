#pragma once

#include <iostream>
#include <fstream>
#include <new>
#include <string>
#include <list>

#include "Utilities.h"
#include "GameObject.h"
#include "Texture.h"
#include "FileNotFoundError.h"
#include "FileFormatError.h"
#include "SDLError.h"
#include "ArkanoidError.h"

class Game;

typedef list<GameObject*>::iterator itStage;
class GameState
{
protected:
	list <GameObject*> stage;
	Game* app;
	
public:
	virtual ~GameState();
	virtual void render();
	virtual void update();
	virtual bool handleEvents(SDL_Event &e); // be careful with self destruction here
};

