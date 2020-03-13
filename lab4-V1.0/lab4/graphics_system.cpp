#pragma once

#pragma once

#include "graphics_system.h"


Sprite::Sprite(SDL_Texture * texture, int width, int height) {
	this->texture = texture;
	this->width = width;
	this->height = height;
}

void Sprite::draw(int x, int y, int angle) {
	GraphicsSystem* graphics_engine;
	graphics_engine->getInstance()->draw(x, y, angle, this);
}

SDL_Texture* Sprite::getTexture() { return texture; }
int Sprite::getWidth() { return width; }
int Sprite::getHeight() { return height; }


void Sprite::destroy() {
	if (this != nullptr && texture != nullptr) SDL_DestroyTexture(texture);
}

GraphicsSystem::GraphicsSystem() {}

GraphicsSystem* GraphicsSystem::getInstance() {
	static GraphicsSystem instance;	// Guaranteed to be destroyed.
									// Instantiated on first use.
	return &instance;
}

void GraphicsSystem::draw(int x, int y, int angle, Sprite* sprite) {
	SDL_Rect rect;

	rect.x = x - sprite->getWidth() / 2.0f;
	rect.y = y - sprite->getHeight() / 2.0f;

	SDL_QueryTexture(sprite->getTexture(), NULL, NULL, &(rect.w), &(rect.h));

	SDL_Point center = { sprite->getWidth() / 2.0f, sprite->getHeight() / 2.0f };
	SDL_RenderCopyEx(renderer, sprite->getTexture(), NULL, &rect, angle, &center, SDL_FLIP_NONE);
}

Sprite * GraphicsSystem::createSprite(const char * path, int width, int height) {

	SDL_Surface* surf = IMG_Load(path);

	if (surf == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to load image %s! SDL_image Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Create texture from surface pixels
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == NULL){
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		return NULL;
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(surf);

	Sprite * sprite = new Sprite(texture, width, height);

	return sprite;
}


void GraphicsSystem::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}