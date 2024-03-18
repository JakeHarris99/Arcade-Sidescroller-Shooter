#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

using namespace std; 

class Score {
public:
	Score(SDL_Renderer*);
	void init();
	void update();
	void draw();
	void clean();
	int playerScore = 0;

private:
	TTF_Font* font;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Color color{ 255,255,255,0 };
	SDL_Rect position{ 20,10,100,50 };
};