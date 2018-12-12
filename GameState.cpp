#include "GameState.h"



GameState::GameState(){
}


GameState::~GameState(){
	for (itStage it = stage.begin(); it != stage.end(); it++)
		delete (*it);
}

void GameState::render() {

}

void GameState::update(){

}

void GameState::handleEvents(SDL_Event &e) {

}

