#include "SDLGameObject.h"
#include "Texture.h"
#include "Game.h"

SDLGameObject::SDLGameObject(Game* gameptr, int posX, int posY, int objectWidth, int objectHeight, Texture* objectTexture, TextureNames textureName) {
	game = gameptr;
	position.setX(posX);
	position.setY(posY);
	width = objectWidth;
	height = objectHeight;
	// texture = game->getTexture(textureName);
}


void SDLGameObject::render() {
	texture->render(getRect());
}


SDL_Rect SDLGameObject::getRect() {
	SDL_Rect rect{ position.getX(), position.getY(), width, height };
	return rect;
}