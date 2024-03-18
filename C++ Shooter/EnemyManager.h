#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include "TileMap.h"
#include <iostream>
#include <ctime>
#include "Lives.h"
#include "BulletManager.h"
#include "Score.h"
#include <math.h>
#include <SDL_mixer.h>

using namespace std;

struct Enemy
{
	int x;
	int y;
	int radius = 15;
};

class EnemyManager{
public:
	EnemyManager(SDL_Renderer * renderer, TileMap * tileMap, Lives * lives, Score * score, BulletManager * bulletManager) : renderer(renderer), tileMap(tileMap), lives(lives), score(score), bulletManager(bulletManager) {}
	Mix_Chunk * soundEffectGround = Mix_LoadWAV("cache/sound/ground.wav");
	Mix_Chunk * soundEffectHit = Mix_LoadWAV("cache/sound/hit.wav");

	void init()
	{
		srand(time(NULL));
		SDL_Surface * surface = IMG_Load("cache/enemy/ball.png");
		this->enemyTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);

		for (int i = 0; i < MAP_SIZE_X; i++)
		{
			floors.push_back({ i*MAP_TILE_SIZE_PX, (MAP_SIZE_Y-1)*MAP_TILE_SIZE_PX, MAP_TILE_SIZE_PX, MAP_TILE_SIZE_PX });
		}
	}

	void update()
	{
		if (SDL_GetTicks() - lastSpawn > ENEMY_SPAWN_TIMER_MS && enemies.size() < MAX_ENEMIES)
		{
			enemies.push_back(Enemy{rand()%800,0});
			lastSpawn = SDL_GetTicks();
		}

		for (auto &b : enemies)
		{
			b.y += ENEMY_SPEED;
			for (auto &f : floors)
			{
				SDL_Rect enemyRect = { b.x, b.y, 30, 30 };
				SDL_Rect nullRect;
				if (SDL_IntersectRect(&enemyRect, &f, &nullRect))
				{
					b.y = 0xCCCCCCCC;
					int tempI = floor(b.x / MAP_TILE_SIZE_PX);
					tileMap->MAP_DATA[MAP_SIZE_Y-1][tempI] = 2;
					if (lives->livesLeft >= 0)
					{
						lives->livesLeft -= 1;
						cout << lives->livesLeft;
					}
					if (lives->livesLeft == -1)
					{
						exit(0);
					}
					Mix_PlayChannel(-1, soundEffectGround, 0);
				}
			}
			for (auto &p : bulletManager->bullets)
			{
				if (sqrt(pow((b.x + b.radius) - (p.x + p.radius), 2) + pow((b.y - b.radius) - (p.y - p.radius), 2)) < p.radius + b.radius)
				{
					b.y = 0xCCCCCCCC;
					p.distance = 1000;
					score->playerScore += 1;
					Mix_PlayChannel(-1, soundEffectHit, 0);
				}
			}
		}
		auto remove = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& b) {return b.y == 0xCCCCCCCC; });
		enemies.erase(remove, enemies.end());
	}

	void draw()
	{
		SDL_Point center = { 15,15 };
		for (auto &b : enemies)
		{
			int random_variable = std::rand();
			SDL_Rect dest = { b.x, b.y, 30, 30 };
			SDL_RenderCopyEx(renderer, enemyTexture, 0, &dest, 0, &center, SDL_FLIP_NONE);
		}
	}

	void clean()
	{
		SDL_DestroyTexture(this->enemyTexture);
	}

private:
	SDL_Renderer * renderer;
	SDL_Texture * enemyTexture;
	vector<Enemy> enemies;
	vector<SDL_Rect> floors;
	TileMap * tileMap;
	Lives * lives;
	Score * score;
	BulletManager * bulletManager;
	const int MAX_ENEMIES = 5;
	const int ENEMY_SPAWN_TIMER_MS = 4000;
	const int ENEMY_SPEED = 1;
	unsigned int lastSpawn = 0;
};