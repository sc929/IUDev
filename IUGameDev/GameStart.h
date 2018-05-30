#ifndef GameStart_h
#define GameStart_h

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class GameStart {

public:
	GameStart();
	~GameStart();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer *renderer;
	static SDL_Event event;

private:
	bool isRunning;
	SDL_Window *window;
};

#endif