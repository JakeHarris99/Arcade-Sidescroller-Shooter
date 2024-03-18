#pragma once
#include <SDL.h>
#include <SDL_image.h>

#define MAP_SIZE_X 10
#define MAP_SIZE_Y 8
#define MAP_TILE_SIZE_PX 80


class TileMap{
public:
	TileMap(SDL_Renderer*);
	void init();
	void draw();
	void clean();

	int MAP_DATA[MAP_SIZE_Y][MAP_SIZE_X] = {
	{12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12},
	{12,12,12,12,12,12,12,12,12,12},
	{0,0,0,0,0,0,0,0,0,0},
	};
private:
	SDL_Texture * mapTileSet;
	SDL_Renderer * renderer;
};