#pragma once

#include <stack>

using namespace std;

class GameState;

class GameStateMachine {
private:
	stack <GameState*> gameStateStack;

public:
	GameStateMachine();
	~GameStateMachine();

	GameState* currentState();

	void pushState(GameState* state);

	void popState();

	void changeState(GameState* state);
};

