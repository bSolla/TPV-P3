#pragma once
#include "GameState.h"
#include "Ball.h"
#include "BlocksMap.h"
#include "Paddle.h"
#include "Wall.h"
#include "InfoBar.h"
#include "Reward.h"


using namespace std;

class PlayState : public GameState {
private:
	itStage firstReward;
	int numRewards = 0;

	itStage paddleIt;
	itStage ballIt;

	InfoBar* infoBar = nullptr;

	bool end = false;
	bool gameOver = false;
	bool levelClear = false;
	bool menu = true;

	uint lives = 3;
	uint currentLevel = 1;
	uint seconds = 0, minutes = 0;
	uint lastTicks = 0, currentTicks = 0;
	uint score = 0;

public:
	PlayState(Game *gamePtr);
	~PlayState();

	virtual void render();

	virtual void update();

	virtual bool handleEvents (SDL_Event &e);
};

