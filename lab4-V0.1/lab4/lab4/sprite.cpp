#pragma once

#include "sprite.h"


Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture) {
	this->renderer = renderer;
	this->texture = texture;
}


void Sprite::draw(int x, int y) {
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));

	//Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void Sprite::destroy() {
	SDL_DestroyTexture(texture);
}