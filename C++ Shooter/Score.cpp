#include "stdafx.h"
#include "Score.h"

Score::Score(SDL_Renderer * renderer)
{
	this->renderer = renderer;
}

void Score::init()
{
	TTF_Init();
	font = TTF_OpenFont("Arial.ttf", 42);
}

void Score::update()
{
	string playerScoreText = "Score: " + to_string(playerScore);
	SDL_Surface* surface = TTF_RenderText_Solid(font, playerScoreText.c_str(), color);
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	position.w = surface->w;
	position.h = surface->h;
	SDL_FreeSurface(surface);
}

void Score::draw()
{
	SDL_RenderCopy(renderer, texture, 0, &position);
}

void Score::clean()
{
	SDL_DestroyTexture(this->texture);
}