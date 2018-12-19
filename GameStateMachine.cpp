#include "GameStateMachine.h"
#include "GameState.h"
#include "Game.h"

GameStateMachine::GameStateMachine() {
	
}


GameStateMachine::~GameStateMachine() {
}

GameState* GameStateMachine::currentState() {
	return gameStateStack.top();
}

void GameStateMachine::pushState(GameState* state) {
	gameStateStack.push(state);
}

void GameStateMachine::popState() {
	if (!gameStateStack.empty()){
		delete gameStateStack.top();
		gameStateStack.pop();
	}
}

void GameStateMachine::changeState(GameState* state) {
	popState();
	pushState(state);
}