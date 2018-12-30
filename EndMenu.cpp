#include "EndMenu.h"
#include "Game.h"


EndMenu::EndMenu (Game *gamePtr, bool won) {
	game = gamePtr;
	win = won; // TODO: use to determine wether to write win or lose

	stage.push_back (new Button (game, buttonPositions[ButtonTypes::BackToMainMenu], backToMainMenu, game->getTexture(TextureNames::buttons), 5));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Exit], endGame, game->getTexture(TextureNames::buttons), 2));
}


EndMenu::~EndMenu () {
	// pointer deletion is made in the base class
}


void EndMenu::backToMainMenu (Game * gamePtr) {
	gamePtr->backToMainMenu ();
}
