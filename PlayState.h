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
// --------------------- variables------------------------------------------------------
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

	uint mapWidth = WIN_WIDTH, mapHeight = WIN_HEIGHT;

// ---------------------- methods ------------------------------------------------------
private:
	// gives the ball and paddle their initial positions, calculated from the map dimensions
	void positionObjects();
	// creates a new reward positioned where the ball hit a block (using the ball SDL_Rect)
	void createReward(SDL_Rect rect);


public:
	PlayState(Game *gamePtr);
	~PlayState();

	// getter functions
	uint getMapWidth() const { return mapWidth; }
	uint getMapHeight() const { return mapHeight; }

	// setter functions
	void setLevelClear() { levelClear = true; }
	void setGameOver() { gameOver = true; }
	void increaseLives() { if (lives < MAX_LIVES) lives++; }
	void decreaseLives () { lives--; if (lives == 0) setGameOver (); else positionObjects (); } 
	void setMapSize (int w, int h) { mapWidth = w; mapHeight = h; }
	void setPaddleSize (double scale);

	// takes in the map dimensions calculated in BlocksMap::load() and scales the walls and window to fit accordingly
	void scaleObjects(uint newMapWidth, uint newMapHeight);
	// returns wether the ball collides with an object or not, and if it does, returns the collision vector
	bool collides(SDL_Rect ballRect, Vector2D ballSpeed, Vector2D &collVector);
	// checks if a reward collides with the paddle
	bool rewardCollides(SDL_Rect rewardRect);
	// deletes an object from the list
	void killObject(itStage it);
	virtual void render();

	virtual void update();

	virtual bool handleEvents (SDL_Event &e);
};

