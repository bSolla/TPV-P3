#include "Reward.h"
#include "Game.h"
#include "PlayState.h"

// ----------- Function object hierarchy to manage the effects of each reward ------------------------
void LevelUp::operator()(PlayState *playStatePtr) {
	playStatePtr->setLevelClear ();
}


void RewardLife::operator()(PlayState *playStatePtr) {
	playStatePtr->increaseLives ();
}


void EnlargePaddle::operator()(PlayState *playStatePtr) {
	playStatePtr->setPaddleSize (MAKE_PADDLE_BIGGER);
}

void ShrinkPaddle::operator()(PlayState *playStatePtr) {
	playStatePtr->setPaddleSize (MAKE_PADDLE_SMALLER);
}

void rewardAction (PlayState *playStatePtr, Action *action) {
	return (*action)(playStatePtr);
}




// ----------------------------------  R E W A R D S  -----------------------------------------------
Reward::Reward (Game *gamePtr, PlayState *playStatePtr, RewardType rewardType) {
	game = gamePtr;
	playState = playStatePtr;
	speed.setY (verticalSpeed);
	width = STANDARD_CELL_HEIGHT * 1.5;
	height = STANDARD_CELL_HEIGHT / 2;
	texture = game->getTexture (TextureNames::rewards);

	setActionType (rewardType);
	setSprites (rewardType);
	type = rewardType;
}


Reward::Reward (Game *gamePtr, PlayState *playStatePtr) {
	game = gamePtr;
	playState = playStatePtr;
	speed.setY (verticalSpeed);
	width = STANDARD_CELL_HEIGHT * 1.5;
	height = STANDARD_CELL_HEIGHT / 2;
	texture = game->getTexture (TextureNames::rewards);
}


Reward::~Reward () {
	delete action;
}


void Reward::setActionType (RewardType rewardType) {
	switch (rewardType) {
	case L: 
		action = new LevelUp ();
		break;
	case R:
		action = new RewardLife ();
		break;
	case E:
		action = new EnlargePaddle ();
		break;
	case S:
		action = new ShrinkPaddle ();
		break;
	default:
		break;
	}
}


void Reward::setSprites (RewardType rewardType) {
	switch (rewardType) {
	case L: 
		spriteSheetRow = 0;
		break;
	case R:
		spriteSheetRow = 4;
		break;
	case E:
		spriteSheetRow = 1;
		break;
	case S:
		spriteSheetRow = 3;
		break;
	default:
		break;
	}
}


void Reward::update () {
	int paddleY = playState->getMapHeight () - STANDARD_CELL_HEIGHT * 3; // one cell used by the info bar, other one as a spacer, and the paddle cell height

	spriteSheetCol++;
	if (spriteSheetCol >= texture->getNumCols ()) {
		spriteSheetCol = 0;
	}	

	MovingObject::update ();

	if (position.getY () > paddleY) {
		if (playState->rewardCollides (getRect())) {
			rewardAction (playState, action);
			playState->killObject (itList);
		}
		else if (position.getY () > paddleY + STANDARD_CELL_HEIGHT) {
			playState->killObject (itList);
		}
	}
}


void Reward::render () {
	texture->renderFrame (getRect (), spriteSheetRow, spriteSheetCol);
}


void Reward::loadFromFile (ifstream & file) {
	int aux;

	MovingObject::loadFromFile (file);

	file >> aux;
	type = RewardType (aux);

	setActionType (type);
	setSprites (type);
}


void Reward::saveToFile (ofstream & file) {
	MovingObject::saveToFile (file);
	file << int(type);
}


