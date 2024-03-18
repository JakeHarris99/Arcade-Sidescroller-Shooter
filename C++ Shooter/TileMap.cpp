#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(SDL_Renderer * renderer)
{
	this->renderer = renderer;
}

void TileMap::init()
{
	SDL_Surface* tileSurface = IMG_Load("cache/tileSet/tileSet.png");
	mapTileSet = SDL_CreateTextureFromSurface(renderer, tileSurface);
	SDL_FreeSurface(tileSurface);
}

void TileMap::draw()
{
	for (int i = 0; i < MAP_SIZE_Y; i++)
	{
		for (int j = 0; j < MAP_SIZE_X; j++)
		{
			SDL_Rect srcRect = { (MAP_DATA[i][j]%6) * 80,((MAP_DATA[i][j])/6) * 80, 80, 80 };
			SDL_Rect destRect = { j*MAP_TILE_SIZE_PX, i*MAP_TILE_SIZE_PX, MAP_TILE_SIZE_PX, MAP_TILE_SIZE_PX };
			SDL_RenderCopy(renderer, mapTileSet, &srcRect, &destRect);
		}
	}
}

void TileMap::clean()
{
	SDL_DestroyTexture(this->mapTileSet);
}