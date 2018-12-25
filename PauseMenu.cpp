#include "PauseMenu.h"
#include "Game.h"


PauseMenu::PauseMenu (Game *gamePtr) {
	game = gamePtr;

	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Play], resume, game->getTexture(TextureNames::buttons), 3));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Save], save, game->getTexture(TextureNames::buttons), 4));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::BackToMainMenu], backToMainMenu, game->getTexture(TextureNames::buttons), 5));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Exit], endGame, game->getTexture(TextureNames::buttons), 2));
}


PauseMenu::~PauseMenu () {
	// pointer deletion is made in the base class
}


void PauseMenu::resume (Game * gamePtr) {
	gamePtr->backToGame ();
}


void PauseMenu::save (Game * gamePtr) {
	cout << "save game\n";
}


void PauseMenu::backToMainMenu (Game * gamePtr) {
	gamePtr->backToMainMenu ();
}
