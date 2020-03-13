#pragma once

#include "sprite.h"


Sprite::Sprite(SDL_Renderer * renderer, SDL_Texture * texture, int width, int height) {
	this->renderer = renderer;
	this->texture = texture;
	this->width = width;
	this->height = height;
}

// todo fix sprite transparency
void Sprite::draw(int x, int y, int angle) {
	SDL_Rect rect;

	rect.x = x - (width / 2.0);
	rect.y = y - (height / 2.0);

	SDL_QueryTexture(texture, NULL, NULL, &(rect.w), &(rect.h));

	//Render texture to screen
	//SDL_RenderCopy(renderer, texture, NULL, &rect);
	SDL_Point center = { width / 2.0f, height / 2.0f};
	SDL_RenderCopyEx(renderer, texture, NULL, &rect, angle, &center, SDL_FLIP_NONE);
}


void Sprite::destroy() {
	SDL_DestroyTexture(texture);
}