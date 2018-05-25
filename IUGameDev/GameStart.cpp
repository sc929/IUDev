#include "GameStart.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <string>

GameObject* player;
GameObject* enemy;

GameStart::GameStart()
{}

GameStart::~GameStart()
{}

void GameStart::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen == true)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "System initialised..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	player = new GameObject("Images\\Tank.png", renderer, 0, 0);
	enemy = new GameObject("Images\\Bullet.png", renderer, 50, 50);
}

void GameStart::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void GameStart::update()
{
	player->Update();
	enemy->Update();
}

void GameStart::render()
{
	SDL_RenderClear(renderer);

	// What to render

	player->Render();
	enemy->Render();


	SDL_RenderPresent(renderer);
}

void GameStart::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}
