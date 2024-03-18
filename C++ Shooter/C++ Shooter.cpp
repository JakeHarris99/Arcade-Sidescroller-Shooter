#include "stdafx.h"
#include "Game.h"
#include <stdio.h>
#include <SDL.h>
#include <iostream>
#undef main

Game * game = nullptr;

int main(int argc, const char * argv[])
{

	game = new Game();

	game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->active())
	{
		game->doInputs();
		game->doUpdate();
		game->doRender();
	}

	game->doShutdown();

	return 0;
}