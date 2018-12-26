#include "PlayState.h"
#include "Game.h"


// TODO: modify all game object constructors so they take in a pointer to Play State too
// Objects done:	
	// Paddle
	// Ball
	// Block
	// BlocksMap
	// Reward
	// 


PlayState::PlayState(Game *gamePtr) {
	game = gamePtr;

	// create game objects
	// push them to the stage
}


PlayState::~PlayState() {
	// pointer deletion is made in the base class
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
			cout << "debug: created reward\n";
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
void PlayState::render() {
	GameState::render ();

	// TODO: time management: infoBar, handleTime()
	//infoBar->render (seconds, minutes, currentLevel, lives);
}

void PlayState::update () {
	cout << "updating playScene\n";
	GameState::update ();
}

bool PlayState::handleEvents (SDL_Event & e) {
	bool handled = false;

	if (e.type == SDL_KEYUP) {
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			game->pauseMenu ();
			handled = true;
		}
	}


	return handled;
}
