#include "stdafx.h"
#include "Player.h"

Player::Player(SDL_Renderer * renderer)
{
	this->playerRenderer = renderer;
}

void Player::init()
{
	SDL_Surface* playerSurface = IMG_Load("cache/player/tank.png");
	playerTexture = SDL_CreateTextureFromSurface(playerRenderer, playerSurface);
	SDL_FreeSurface(playerSurface);

	for (int i = 0; i < 256; i++)
	{
		keyDown[i] = false;
	}
}

void Player::processInput(SDL_Event e)
{
	switch (e.type) //Checks event type in switch
	{
	case SDL_KEYDOWN:
		if (e.key.keysym.scancode < 512)
		{
			keyDown[e.key.keysym.scancode] = true;
		}
		break;

	case SDL_KEYUP:
		if (e.key.keysym.scancode < 512)
		{
			keyDown[e.key.keysym.scancode] = false;
		}
		break;

	default:
		break;
	}
}

void Player::update()
{
	if (getKeyDown(SDL_SCANCODE_RIGHT))
	{
		position.x += 5;
	}
	if (getKeyDown(SDL_SCANCODE_LEFT))
	{
		position.x -= 5;
	}

	Uint32 ticks = SDL_GetTicks();
	Uint32 sprite = (ticks / 500) % 8;
	srcRect = { int(sprite) * 74, 0, 74, 64 };
}

void Player::draw()
{
	SDL_RenderCopy(playerRenderer, playerTexture, &srcRect, &position);
}

void Player::clean()
{
	SDL_DestroyTexture(this->playerTexture);
}