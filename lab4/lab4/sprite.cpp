#pragma once

#include "sprite.h"


Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture, int width) {
	this->renderer = renderer;
	this->texture = texture;
	this->width = width;
}

// todo fix sprite transparency
void Sprite::draw(int x, int y) {
	SDL_Rect rect;

	rect.x = x - (width / 2.0);
	rect.y = y - (width / 2.0);

	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));

	//Render texture to screen
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}


void Sprite::destroy() {
	SDL_DestroyTexture(texture);
}