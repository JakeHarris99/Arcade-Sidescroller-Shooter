#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Sound.h"
#include <SDL_mixer.h>

using namespace std;

struct Bullet
{
	int distance = 0;
	int x;
	int y;
	int radius = 10;
};

class BulletManager {
public:
	BulletManager(SDL_Renderer * renderer, Player * player) : renderer(renderer), player(player) {}
	vector<Bullet> bullets;
	Mix_Chunk * soundEffect = Mix_LoadWAV("cache/sound/shoot.wav");

	void init()
	{
		SDL_Surface * surface = IMG_Load("cache/missile/missile.png");
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	void processInput()
	{
		if(player->keyDown[SDL_SCANCODE_SPACE])
		{
			if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS)
			{
				Mix_PlayChannel(-1, soundEffect, 0);
				bullets.push_back(Bullet{0, player->position.x+player->position.w/2, player->position.y});
				lastShot = SDL_GetTicks();
			}
		}
	}

	void update()
	{
		for (auto &b : bullets)
		{
			b.y -= BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}

		auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {return b.distance > 1000; });
		bullets.erase(remove, bullets.end());
	}

	void draw()
	{
		SDL_Point center = { 10,10 };
		for (auto &b : bullets)
		{
			SDL_Rect dest = { b.x, b.y, 20, 20 };
			SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, 0, &center, SDL_FLIP_NONE);
		}
	}

	void clean()
	{
		SDL_DestroyTexture(this->bulletTexture);
		Mix_FreeChunk(soundEffect);
	}
private:
	SDL_Renderer * renderer;
	SDL_Texture * bulletTexture;
	Player * player;

	const int SHOOT_TIMER_MS = 300;
	const int BULLET_VELOCITY = 15;
	unsigned int lastShot = 0;
};