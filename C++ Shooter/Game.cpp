#include "stdafx.h"
#include "Game.h"
#include "SDL.h"
#include <iostream>

bool Game::checkClickIntersect(int x, int y, struct SDL_Rect *rect)
{
	if (x >= rect->x && x < (rect->x + rect->w))
	{
		if (y >= rect->y && y < (rect->y + rect->h))
		{
			return true;
		}
	}
	return false;
}

void Game::init(const char *gameTitle, int xpos, int ypos, int gameWidth, int gameHeight, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN; //Sets flag to be fullscreen
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //Checks if SDL launches successfully
	{
		std::cout << "SDL Successfully Launched\n"; //Confirms in console

		window = SDL_CreateWindow(gameTitle, xpos, ypos, gameWidth, gameHeight, flags); //Creates an SDL window instance
		if (window) //Check windows has been created
		{
			std::cout << "SDL Window Created\n"; //Confirms in console
		}

		renderer = SDL_CreateRenderer(window, -1, 0); //Creates an SDL renderer instance with window 
		if (renderer) //Check if renderer has been created successfully
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			std::cout << "Renderer Created\n"; //Confirms in console
		}

		isActive = true; //Confirms SDL isActive
	}
	else
	{
		isActive = false; //Error has occured and SDL is not active
	}

	sound->init();
	tileMap = new TileMap(this->renderer);
	tileMap->init();
	score = new Score(this->renderer);
	score->init();
	lives = new Lives(this->renderer);
	lives->init();
	player = new Player(this->renderer);
	player->init();
	bulletManager = new BulletManager(this->renderer, this->player);
	bulletManager->init();
	enemyManager = new EnemyManager(this->renderer, this->tileMap, this->lives, this->score, this->bulletManager);
	enemyManager->init();
}

void Game::doInputs() //Handles game inputs
{
	SDL_Event event; //Stores game events
	SDL_PollEvent(&event); //Assigns current event to event variable

	switch (event.type) //Checks event type in switch
	{
	case SDL_QUIT: //Set active to false if the game window is closed
		isActive = false;
		break;

	case SDL_MOUSEBUTTONDOWN:
		mx = event.motion.x;
		my = event.motion.y;
		break;

	case SDL_MOUSEBUTTONUP:
		mx = 0;
		my = 0;
		break;

	default:
		break;
	}

	player->processInput(event);
	bulletManager->processInput();
}

void Game::doUpdate() //Handles game updates
{
	player->update();
	bulletManager->update();
	enemyManager->update();
	score->update();
}

void Game::doRender() //Handles game assets rendering
{
	SDL_RenderClear(renderer); //Clears renderer to be re-rendered
	tileMap->draw();
	player->draw();
	bulletManager->draw();
	enemyManager->draw();
	lives->draw();
	score->draw();
	SDL_RenderPresent(renderer); //Render to the window with the current renderer
	SDL_Delay(16);
}

void Game::doShutdown() //Handles cleaning up the rpogram for optimisation etc
{
	tileMap->clean();
	if (tileMap)
	{
		delete tileMap;
		tileMap = nullptr;
	}
	player->clean();
	if (player)
	{
		delete player;
		player = nullptr;
	}
	bulletManager->clean();
	if (bulletManager)
	{
		delete bulletManager;
		bulletManager = nullptr;
	}
	enemyManager->clean();
	if (enemyManager)
	{
		delete enemyManager;
		enemyManager = nullptr;
	}
	lives->clean();
	if (lives)
	{
		delete lives;
		lives = nullptr;
	}
	score->clean();
	if (score)
	{
		delete score;
		score = nullptr;
	}
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}