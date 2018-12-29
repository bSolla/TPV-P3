#include "Game.h"


Game::Game() {
	iniSDL ();
	iniTextures ();

	stateMachine = new GameStateMachine ();
	stateMachine->pushState (new MainMenu (this));
}


Game::~Game() {
	delete stateMachine;	// the individual states are deleted within GameStateMachine (in its destructor)
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


void Game::loadFromFile(string code) {
	ifstream file;
	int level, secs, mins;

	file.open(LEVELS_PATH + code + SAVE_EXTENSION);
	if (file.is_open()) {
		file >> level >> secs >> mins;
		
		if (level > MAX_LEVEL) {
			throw FileFormatError ("Level bigger than the maximum level\n");
		}

		stateMachine->pushState (new PlayState (this, level, secs, mins));
		static_cast<PlayState*>(stateMachine->currentState ())->loadFromFile (file);

		file.close();
	}
	else
		throw FileNotFoundError(code + SAVE_EXTENSION);

}


void Game::saveToFile() { // TODO: use ttf to write the numbers the player selects in the screen (better feedback means better experience)
	ofstream file;
	try {
		SDL_RenderClear (renderer); // to give the player some feedback that the button was actually pushed
		SDL_RenderPresent (renderer);

		string code = pickFileName ();
		file.open (LEVELS_PATH + code + SAVE_EXTENSION);

		if (file.is_open()) {
			backToGame ();

			static_cast<PlayState*>(stateMachine->currentState ())->saveToFile (file);
		
			file.close ();
		}
		else
			throw (FileNotFoundError (code + SAVE_EXTENSION));
		}
	catch (ArkanoidError err) {
		cout << err.what ();
	}
}


string Game::pickFileName () {
	SDL_Event sdlEvent;
	bool done = false;
	stringstream name;

	while (!done) {
		try {
			if (SDL_PollEvent (&sdlEvent)) {
				if (sdlEvent.type == SDL_QUIT) {
					exit = true;
					throw (ArkanoidError ("Aborted save\n"));
				}
				if (sdlEvent.type == SDL_KEYDOWN) {
					switch (sdlEvent.key.keysym.sym) {
					case SDLK_0:
						name << "0";
						break;
					case SDLK_1:
						name << "1";
						break;
					case SDLK_2:
						name << "2";
						break;
					case SDLK_3:
						name << "3";
						break;
					case SDLK_4:
						name << "4";
						break;
					case SDLK_5:
						name << "5";
						break;
					case SDLK_6:
						name << "6";
						break;
					case SDLK_7:
						name << "7";
						break;
					case SDLK_8:
						name << "8";
						break;
					case SDLK_9:
						name << "9";
						break;
					case SDLK_RETURN:
						done = true;
					default:
						throw (FileFormatError (WRONG_TYPE));
						break;
					}// switch
				}
			}
		}
		catch (FileFormatError err) {
			cout << err.what ();
			cout << "Only numbers from 0 to 9 valid\n";
		}
	}// while !done

	return name.str ();
}


void Game::startGame () {
	stateMachine->pushState (new PlayState (this));
}


void Game::pauseMenu () {
	setWindowSize (WIN_WIDTH, WIN_HEIGHT);
	stateMachine->pushState (new PauseMenu (this));
}


void Game::backToGame () {
	int h = WIN_HEIGHT;
	int w = WIN_WIDTH;

	getStateMachine ()->popState ();

	if (dynamic_cast<PlayState*>(stateMachine->currentState()) != nullptr) { 
		h = dynamic_cast<PlayState*>(stateMachine->currentState ())->getMapHeight ();
		w = dynamic_cast<PlayState*>(stateMachine->currentState ())->getMapWidth ();
	}
	setWindowSize (w, h);
}


void Game::backToMainMenu () {
	backToGame (); 
	getStateMachine ()->popState ();

	setWindowSize (WIN_WIDTH, WIN_HEIGHT);
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

		SDL_Delay (DELAY);
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
}
