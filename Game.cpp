#include "Game.h"


Game::Game() {
	iniSDL ();
	iniTextures ();

	stateMachine = new GameStateMachine ();
	stateMachine->pushState (new MainMenu (this));
}


Game::~Game() {
	// TODO: delete states
}


void Game::iniSDL () {
	SDL_Init(SDL_INIT_EVERYTHING); 
	
	window = SDL_CreateWindow("test", WIN_X, WIN_Y, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); 
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); 
	
	if (window == nullptr || renderer == nullptr) {
		throw SDLError(SDL_GetError());
	}
}


void Game::iniTextures () {
	string errorMsg;

	for (uint i = 0; i < NUM_TEXTURES; ++i) {
		textures[i] = new Texture(renderer, IMAGES_PATH + TEXTURE_ATTRIBUTES[i].filename, TEXTURE_ATTRIBUTES[i].rows, TEXTURE_ATTRIBUTES[i].cols);
	}

	errorMsg = SDL_GetError();
	if (errorMsg != "")
		throw SDLError(errorMsg);
}


void Game::renderInstructions () {
	SDL_Rect destRect { 0, 0, WIN_WIDTH, WIN_HEIGHT };
	
	SDL_RenderClear (renderer);

	textures[TextureNames::instructions]->render (destRect);

	SDL_RenderPresent (renderer);
}


void Game::renderNumberButtons () {
	uint numbersCellSize = WIN_HEIGHT / 10;
	SDL_Rect destRect { 0, WIN_HEIGHT - numbersCellSize, WIN_WIDTH, numbersCellSize };

	textures[TextureNames::menuNumbers]->render(destRect);

	SDL_RenderPresent (renderer);
}


bool Game::handleNumberButtons (SDL_Event SDLevent, int &number) {
	int mouseX, mouseY;
	int numberCellSize = WIN_WIDTH / 10;
	int numbersY = WIN_HEIGHT - numberCellSize;
	int index = 0;
	bool click = false;

	SDL_GetMouseState (&mouseX, &mouseY);

	if ((mouseX > 0 && mouseX < numberCellSize) &&
		(mouseY > 0 && mouseY < numberCellSize)) { // click on the finish button
		click = true;
		number = -1;
	}
	else {
		while (!click && index < 10) {
			if ((mouseX > (index * numberCellSize) && mouseX < ((index + 1) * numberCellSize)) &&
				(mouseY > numbersY && mouseY < WIN_HEIGHT)) { // click on each of the numbers
				click = true;
				number = index;
			}

			index++;
		} //while
	} // else

	return click;
}


void Game::startGame () {
	stateMachine->pushState (new PlayState (this));
}


void Game::pauseMenu () {
	stateMachine->pushState (new PauseMenu (this));
}


void Game::handleEvents () {
	SDL_Event ev;  

	if (SDL_PollEvent (&ev)) {
		if (ev.type == SDL_QUIT) {
			exit = true;
		}
		else {
			stateMachine->currentState ()->handleEvents (ev);
		}
	}
}


void Game::run () {
	while (!exit) {
		update ();
		handleEvents ();
	}
}


void Game::render () {
	SDL_RenderClear (renderer);

	stateMachine->currentState ()->render ();

	SDL_RenderPresent (renderer);
}


void Game::update () {
	stateMachine->currentState ()->update ();

	render ();

	// handleTime ();
}
