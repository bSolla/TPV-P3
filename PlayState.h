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
	// if the control bool levelClear is true, deletes the old BlocksMap, creates a new one and reads all the corresponding info
	void handleLevelUp();
	// keeps track of the time elapsed since starting a level
	void handleTime();

public:
	PlayState(Game *gamePtr);
	// used when loading a file 
	PlayState (Game *gamePtr, uint lev, uint secs, uint mins);
	~PlayState();

	// getter functions
	uint getMapWidth() const { return mapWidth; }
	uint getMapHeight() const { return mapHeight; }

	// setter functions
	void setLevelClear() { levelClear = true; }
	void setGameOver ();
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
	// calls the render method of all stage objects
	virtual void render();
	// calls the update method of all stage objects
	virtual void update();
	// checks for esc and if it hasnt been pushed calls the handle events method of all stage objects
	virtual bool handleEvents (SDL_Event &e);
	// calls the load from file method of all stage objects 
	void loadFromFile (ifstream &file);
	// calls the save to file method of all stage objects
	void saveToFile(ofstream &file);
};

