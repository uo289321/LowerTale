#include "Text.h"

Text::Text(string content, float x, float y, Game* game) {
	this->content = content;
	this->x = x;
	this->y = y;
	this->game = game;
	this->r = 255;
	this->g = 255;
	this->b = 255;
	this->a = 255;
}



void Text::highlight() {
	this->b = 0;
}

void Text::unhighlight() {
	this->b = 255;
}

void Text::show() {
	this->a = 255;
}

void Text::hide() {
	this->a = 0;
}

void Text::draw() {
	SDL_Color color;
	color.r = this->r;
	color.g = this->g;
	color.b = this->b;
	color.a = this->a; //transparente

	SDL_Surface* surface = TTF_RenderText_Blended(game->font, content.c_str(), color);
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
