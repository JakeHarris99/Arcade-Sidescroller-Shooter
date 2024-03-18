#include "stdafx.h"
#include "Player.h"
#include "TileMap.h"
#include "score.h"
#include "Lives.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include <stdio.h>
#include "SDL.h"
#include <SDL_image.h>
#include <iostream>

class Game
{

public:

	bool checkClickIntersect(int x, int y, struct SDL_Rect *rect);
	void init(const char* gameTitle, int xpos, int ypos, int gameWidth, int gameHeight, bool fullscreen);

	void doInputs();
	void doUpdate();
	void doRender();
	void doShutdown();

	bool active() { return isActive; };

private:
	bool isActive = true;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Sint32 mx;
	Sint32 my;
	Player * player;
	TileMap * tileMap;
	Lives * lives;
	Score * score;
	Sound * sound;
	BulletManager * bulletManager;
	EnemyManager * enemyManager;
};