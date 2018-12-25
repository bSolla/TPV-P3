#include "MainMenu.h"
#include "Game.h"



MainMenu::MainMenu (Game *gamePtr) { // TODO: change the row number for an enum type so its easier to understand
	game = gamePtr;
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Play], play, game->getTexture(TextureNames::buttons), 0));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Load], load, game->getTexture(TextureNames::buttons), 1));
	stage.push_back (new Button (game, buttonPositions[ButtonTypes::Exit], endGame, game->getTexture(TextureNames::buttons), 2));
}


MainMenu::~MainMenu () {
	// pointer deletion is made in the base class
}


void MainMenu::play (Game * gamePtr) {
	gamePtr->startGame ();
}


void MainMenu::load (Game * gamePtr) {
	SDL_Event SDLevent;
	stringstream numberSequence;
	string fileName;
	int number = -2;
	uint iterations = 0;
	bool click = false;
	bool end = false;

	SDL_Rect destRect { 0, WIN_HEIGHT / 2, STANDARD_CELL_HEIGHT, STANDARD_CELL_HEIGHT };

	gamePtr->renderInstructions ();
	gamePtr->renderNumberButtons ();

	do {
		// get the numbers and store them in a stream + render them
		if (SDL_PollEvent (&SDLevent)) {
			if (SDLevent.type == SDL_QUIT) {
				end = false;
				gamePtr->setExit (true);
			}
			if (SDLevent.type == SDL_MOUSEBUTTONUP) {
				click = gamePtr->handleNumberButtons (SDLevent, number);
			}
		}

		if (click) {
			if (number != -1) {
				numberSequence << number;

				// render the chosen number in screen
				destRect.x = iterations * STANDARD_CELL_HEIGHT;
				gamePtr->getTexture(TextureNames::menuNumbers)->renderFrame (destRect, 0, number);
				SDL_RenderPresent (gamePtr->getRenderer());

				iterations++;
			}
			click = false;
		}
	} while (number != -1 && !end);

	fileName = LEVELS_PATH + numberSequence.str () + LEVEL_EXTENSION;

	try { gamePtr->loadFromFile (numberSequence.str ()); }
	catch (FileFormatError err) {
		cout << err.what ();
	}
	catch (ArkanoidError err) {
			cout << err.what ();
	}
}

