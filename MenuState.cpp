#include "MenuState.h"
#include "Game.h"



MenuState::MenuState() {
}


MenuState::~MenuState() {
	// pointer deletion is made in the base class
}


void MenuState::endGame (Game * gamePtr) {
	gamePtr->setExit (true);
}
