#include "PauseMenu.h"
#include "Game.h"


PauseMenu::PauseMenu () {
}


PauseMenu::~PauseMenu () {
}


void PauseMenu::resume (Game * gamePtr) {
	gamePtr->getStateMachine ()->popState ();
}


void PauseMenu::save (Game * gamePtr) {

}


void PauseMenu::backToMainMenu (Game * gamePtr) {

}
