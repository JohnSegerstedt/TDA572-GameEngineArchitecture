#include "text_system.h"


void TextSystem::drawText(int x, int y, const char* msg) {
	SDL_Color black = { 0, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

	SDL_Surface* surf = TTF_RenderText_Solid(font, msg, black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

	SDL_Texture* msg_texture = SDL_CreateTextureFromSurface(renderer, surf); //now you can convert it into a texture

	int w = 0;
	int h = 0;
	SDL_QueryTexture(msg_texture, NULL, NULL, &w, &h);
	SDL_Rect dst_rect = { x, y, w, h };

	SDL_RenderCopy(renderer, msg_texture, NULL, &dst_rect);

	SDL_DestroyTexture(msg_texture);
	SDL_FreeSurface(surf);
}

void TextSystem::setRenderer(SDL_Renderer* renderer) {
	this->renderer = renderer;
}

void TextSystem::setFont(TTF_Font* font) {
	this->font = font;
}

void TextSystem::destroyFont() {
	TTF_CloseFont(font);
}