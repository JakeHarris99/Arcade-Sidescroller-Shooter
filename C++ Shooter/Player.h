#pragma once
#include <SDL.h>
#include <SDL_image.h>
class Player {
public:
	Player(SDL_Renderer*);
	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();

	bool getKeyDown(int keyCode)
	{
		if (keyCode > 0 && keyCode < 512)
		{
			return this->keyDown[keyCode];
		}
		return false;
	}
	SDL_Rect position{ 326, 432, 148, 128 };
	bool keyDown[256];

private:
	SDL_Rect srcRect;
	SDL_Texture * playerTexture;
	SDL_Renderer * playerRenderer;
};
