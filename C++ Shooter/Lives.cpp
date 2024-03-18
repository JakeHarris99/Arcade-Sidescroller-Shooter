#include "stdafx.h"
#include "Lives.h"

Lives::Lives(SDL_Renderer * renderer)
{
	this->renderer = renderer;
}

void Lives::init()
{
	SDL_Surface* surface = IMG_Load("cache/lives/lives.png");
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

void Lives::draw()
{
	switch (livesLeft)
	{
	case 3:
		SDL_RenderCopy(renderer, texture, &srcRectThree, &position);
		break;
	case 2:
		SDL_RenderCopy(renderer, texture, &srcRectTwo, &position);
		break;
	case 1:
		SDL_RenderCopy(renderer, texture, &srcRectOne, &position);
		break;
	case 0:
		SDL_RenderCopy(renderer, texture, &srcRectZero, &position);
		break;
	default:
		break;
	}
}

void Lives::clean()
{
	SDL_DestroyTexture(this->texture);
}