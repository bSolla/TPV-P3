#include "MenuState.h"
#include "Game.h"



MenuState::MenuState() {
}


MenuState::~MenuState() {
}


void MenuState::endGame (Game * gamePtr) {
	gamePtr->setExit (true);
}
