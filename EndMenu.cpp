#include "EndMenu.h"
#include "Game.h"


EndMenu::EndMenu (Game *gamePtr, bool won) {
	game = gamePtr;
	background = game->getTexture (TextureNames::endmenuTextures);

	win = won; 
	if (!win) {
		row = 1;
	}

	stage.push_back (new Button (game, buttonPositions[ButtonTypes::BackToMainMenu], backToMainMenu, game->getTexture(TextureNames::buttons), 5));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Exit], endGame, game->getTexture(TextureNames::buttons), 2));
}


EndMenu::~EndMenu () {
	background = nullptr;
	// pointer deletion is made in the base class
}


void EndMenu::backToMainMenu (Game * gamePtr) {
	gamePtr->backToMainMenu ();
}


 void EndMenu::render () { 
	 background->renderFrame (FULL_WINDOW_RECT, row, 0);
	 MenuState::render (); 
 }