#include "AnimatedText.h"
#include <string>

AnimatedText::AnimatedText(string content, float x, float y, Game* game) {
	this->content = content;
	this->x = x;
	this->y = y;
	this->game = game;
	this->shown = content.substr(0, n);
}

bool AnimatedText::update() {
	this->n++;
	this->shown = content.substr(0, n);
	if (n == content.length())
		return true;
	return false;
}

void AnimatedText::draw() {
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255; //transparente

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, shown.c_str(), color);
	// c_str() transforma el string a cost *char;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(game->renderer, surface);

	SDL_Rect rect; // Base de coordenadas esquina superior izquierda
	rect.x = x - surface->w / 2;
	rect.y = y - surface->h / 2;
	rect.w = surface->w;
	rect.h = surface->h;

	SDL_FreeSurface(surface);
	SDL_RenderCopy(game->renderer, texture, NULL, &rect);
	SDL_DestroyTexture(texture);
}