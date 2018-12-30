#include "PlayState.h"
#include "Game.h"


PlayState::PlayState(Game *gamePtr) {
	game = gamePtr;

	stage.push_back (new BlocksMap (game, this));

	stage.push_back (new Wall (game, this, game->getTexture (TextureNames::sideWall))); // leftW
	stage.push_back (new Wall (game, this, game->getTexture (TextureNames::sideWall))); // rightW
	stage.push_back (new Wall (game, this, game->getTexture (TextureNames::topWall))); // topW

	stage.push_back (new Ball (game, this));
	ballIt = stage.end(); // ballIt set past the end
	ballIt--; // ballIt actually pointing to the position in the list

	stage.push_back (new Paddle (game, this));
	paddleIt = stage.end (); // paddleIt set past the end
	paddleIt--; //paddleIt actually pointing to the position in the list

	firstReward = stage.end ();

	// loads the level into BlocksMap
	if (dynamic_cast<BlocksMap*>(*stage.begin ()) != nullptr) {
		dynamic_cast<BlocksMap*>(*stage.begin ())->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
	}
	else
		throw ArkanoidError ("Casting error\n");

	infoBar = new InfoBar (game, this);

	positionObjects ();
}


PlayState::PlayState (Game *gamePtr, uint lev, uint secs, uint mins) {
	currentLevel = lev;
	seconds = secs;
	minutes = mins;
	game = gamePtr;

	stage.push_back (new BlocksMap (game, this));

	stage.push_back (new Wall (game, this, game->getTexture (TextureNames::sideWall))); // leftW
	stage.push_back (new Wall (game, this, game->getTexture (TextureNames::sideWall))); // rightW
	stage.push_back (new Wall (game, this, game->getTexture (TextureNames::topWall))); // topW

	stage.push_back (new Ball (game, this));
	ballIt = stage.end(); // ballIt set past the end
	ballIt--; // ballIt actually pointing to the position in the list

	stage.push_back (new Paddle (game, this));
	paddleIt = stage.end (); // paddleIt set past the end
	paddleIt--; //paddleIt actually pointing to the position in the list

	firstReward = stage.end ();
}


PlayState::~PlayState() {
	// stage pointer deletion is made in the base class
	delete infoBar;
}


void PlayState::positionObjects () {
	// position paddle -------------------------------------
	if (dynamic_cast<Paddle*>(*paddleIt) != nullptr) { 
		dynamic_cast<Paddle*>(*paddleIt)->setInitialPosition (mapWidth, mapHeight - STANDARD_CELL_HEIGHT * 3);
	}
	else
		throw ArkanoidError ("Casting error\n");

	// position ball --------------------------------------
	if (dynamic_cast<Ball*>(*ballIt) != nullptr) { 
		dynamic_cast<Ball*>(*ballIt)->setInitialPosition (mapWidth, mapHeight - STANDARD_CELL_HEIGHT * 4);
	}
	else
		throw ArkanoidError ("Casting error\n");
}


void PlayState::scaleObjects (uint newMapWidth, uint newMapHeight) {
	mapHeight = newMapHeight;
	mapWidth = newMapWidth;

	itStage wallIt = stage.begin (); // it points to map for now
	wallIt++; // but now it points to the first wall

	// we can't make it in a loop because each wall has unique scale

	// left wall -------------------------------------------
	if (dynamic_cast<Wall*>(*wallIt) != nullptr) { 
		dynamic_cast<Wall*>(*wallIt)->setScale (mapHeight - STANDARD_CELL_HEIGHT, WALL_THICKNESS, WallType::leftW); // -STANDARD_CELL_HEIGHT to account for the info bar
	}
	else
		throw ArkanoidError ("Casting error\n");
	wallIt++;

	// right wall ----------------------------------------
	if (dynamic_cast<Wall*>(*wallIt) != nullptr) { 
		dynamic_cast<Wall*>(*wallIt)->setScale (mapHeight - STANDARD_CELL_HEIGHT, WALL_THICKNESS, WallType::rightW);
	}
	else
		throw ArkanoidError ("Casting error\n");
	wallIt++;

	// top wall ------------------------------------------
	if (dynamic_cast<Wall*>(*wallIt) != nullptr) { 
		dynamic_cast<Wall*>(*wallIt)->setScale (WALL_THICKNESS, mapWidth, WallType::topW);
	}
	else
		throw ArkanoidError ("Casting error\n");

	game->setWindowSize (mapWidth, mapHeight);
}


void PlayState::setPaddleSize (double scale) {
	if (dynamic_cast<Paddle*>(*paddleIt) != nullptr) { 
		dynamic_cast<Paddle*>(*paddleIt)->changeSize (scale);
	}
	else
		throw ArkanoidError ("Casting error\n");
}


bool PlayState::collides (SDL_Rect ballRect, Vector2D ballSpeed, Vector2D &collVector) {
	bool ballCollides = false;
	Block* blockPtr = nullptr;
	itStage it = stage.begin (); // it starts pointing at the map

	// ----------------------------------------------- if collides with the blocks...
	if (dynamic_cast<BlocksMap*>(*it) != nullptr) { 
		blockPtr = dynamic_cast<BlocksMap*>(*it)->collides (ballRect, ballSpeed, collVector);
	}
	else
		throw ArkanoidError ("Casting error\n");
	if (blockPtr != nullptr) {
		srand (currentTicks);
		int rewardRand = rand () % 3; // random number [0, 5] to check if a reward is created
		
		ballCollides = true;
		dynamic_cast<BlocksMap*>(*it)->setBlockNull (blockPtr);

		if (rewardRand < 1) {
			createReward (ballRect);
		}
	}
	
	++it; // it now points to the first wall
	// ----------------------------------------------- if collides with any of the walls or the paddle...
	while (it != firstReward && !ballCollides) { // the paddle is the last object before the rewards
		ballCollides = (*it)->collides (ballRect, collVector);
		++it;
	}

	return ballCollides;
}


bool PlayState::rewardCollides (SDL_Rect rewardRect) {
	Vector2D dummyVector2D;
	bool ret = false;

	if (dynamic_cast<Paddle*>(*paddleIt) != nullptr) { 
		ret = dynamic_cast<Paddle*>(*paddleIt)->collides (rewardRect, dummyVector2D);
	}
	else
		throw ArkanoidError ("Casting error\n");

	return ret;
}


void PlayState::createReward (SDL_Rect rect) {
	srand (currentTicks);
	int rewardType = rand () % 4;
	Reward *r = new Reward (game, this, RewardType (rewardType));
	r->setPosition (rect);

	stage.push_back (r);
	itStage itLastReward = --(stage.end ());
	if (firstReward == stage.end ()) {
		firstReward = itLastReward;
	}

	numRewards++;
	r->setItList (itLastReward);
}


void PlayState::killObject (itStage it) {
	if (it == firstReward) {
		firstReward++;
	}

	delete *it;
	stage.erase (it);

	numRewards--;
}


bool PlayState::handleEvents (SDL_Event & e) {
	bool handled = false;

	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			game->pauseMenu ();
			return true;
		}
	}
	
	// only checks if esc hasnt been pushed
	handled = GameState::handleEvents (e);

	return handled;
}


void PlayState::handleLevelUp () {
	if (levelClear) {
		delete (*stage.begin ());// delete the old map and make to new one for the new level
		stage.erase (stage.begin ());
		stage.push_front (new BlocksMap (game, this)); // new map

		delete infoBar; // delete the old info bar to make a new one

		while (numRewards > 0) {
			killObject (firstReward);
		}

		currentLevel++;

		if (currentLevel > MAX_LEVEL)
			game->endMenu (true);
		else {
			// static cast because we know for sure that the first object is the map (it was created within this method)
			static_cast<BlocksMap*>(*stage.begin())->load (LEVEL_SHARED_NAME + to_string (currentLevel) + LEVEL_EXTENSION);
			
			seconds = 0;
			minutes = 0;

			infoBar = new InfoBar (game, this);
			positionObjects ();

			levelClear = false;
		}
	}
}


void PlayState::handleTime () {
	currentTicks = SDL_GetTicks ();

	if (currentTicks > lastTicks + MILLISECONDS_IN_A_TICK) {
		seconds++;

		if (seconds > 59) {
			seconds = 0;
			minutes++;
		}

		lastTicks = currentTicks;
	}
}


void PlayState::setGameOver () { 
	game->endMenu (false); 
}


void PlayState::render() {
	infoBar->render (seconds, minutes, currentLevel, lives);
	
	GameState::render ();
}


void PlayState::update () {
	GameState::update ();

	handleLevelUp ();
	handleTime ();
}


void PlayState::loadFromFile (ifstream & file) { // in this method we use static cast to the base class of all game objects in the playscene, because we need to call load from file (which wouldn't make sense in SDLObject as a button wouln't need to load itself from a file)
	itStage it = stage.begin ();
	static_cast<ArkanoidObject*>(*it)->loadFromFile(file); // loads map
	++it;

	infoBar = new InfoBar (game, this);

	for (it; it != stage.end(); ++it) {
		static_cast<ArkanoidObject*>(*it)->loadFromFile(file);
	}

	file >> numRewards;
	firstReward = stage.end ();

	for (uint i = 0; i < numRewards; ++i) {
		stage.push_back (new Reward (game, this));
		it = stage.end ();
		--it;

		static_cast<ArkanoidObject*>(*it)->loadFromFile (file);
		static_cast<Reward*>(*it)->setItList (it);
	}

	game->setWindowSize (mapWidth, mapHeight);
}


void PlayState::saveToFile (ofstream & file) { // static cast to Arkanoid object: see method above for our explanation
	file << currentLevel << " " << seconds << " " << minutes << "\n";

		for (itStage it = stage.begin (); it != firstReward; ++it) {
			static_cast<ArkanoidObject*>(*it)->saveToFile (file);
			file << "\n";
		}

		file << numRewards << "\n";

		for (itStage it = firstReward; it != stage.end (); ++it) {
			static_cast<ArkanoidObject*>(*it)->saveToFile (file);
			file << "\n";
		}
}
