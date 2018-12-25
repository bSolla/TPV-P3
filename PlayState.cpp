#include "PlayState.h"
#include "Game.h"

// TODO: change all iterators to the stage from auto to itStage, in every Game State

// TODO: modify all game object constructors so they take in a pointer to Play State too
// Objects done:	
	// Paddle
	//


PlayState::PlayState(Game *gamePtr) {
	game = gamePtr;

	// create game objects
	// push them to the stage
}


PlayState::~PlayState() {
	// pointer deletion is made in the base class
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
			// TODO: when Rewards are ready, migrate createReward from Game to PlayState (look at the P2 version for the code)
			//createReward (ballRect);
			cout << "debug: created reward\n";
		}
	}

	// TODO: fix the iterators/castings so we can check the collisions

	//
	//++it; // it now points to the first wall
	//// ----------------------------------------------- if collides with any of the walls or the paddle...
	//while (it != firstReward && !ballCollides) { // the paddle is the last object before the rewards
	//	ballCollides = (*it)->collides (ballRect, collVector);
	//	++it;
	//}

	return ballCollides;
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
