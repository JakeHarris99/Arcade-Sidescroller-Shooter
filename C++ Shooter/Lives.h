#pragma once
#include <SDL.h>
#include <SDL_image.h>

class Lives {
public:
	Lives(SDL_Renderer*);
	void init();
	void draw();
	void clean();
	int livesLeft = 3;

private:
	SDL_Rect position{ 666, 20, 114, 32 };
	SDL_Rect srcRectZero{ 342,0,114,32 };
	SDL_Rect srcRectOne{ 228,0,114,32 };
	SDL_Rect srcRectTwo{ 114,0,114,32 };
	SDL_Rect srcRectThree{ 0,0,114,32 };
	SDL_Texture * texture;
	SDL_Renderer * renderer;
};