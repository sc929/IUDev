#include "GameStart.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"

GameObject* player;
GameObject* enemy;
Map* map;
SDL_Renderer* GameStart::renderer = nullptr;

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
		//System initialised...

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			//Window created!
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			//Renderer created
		}

		isRunning = true;
	}

	player = new GameObject("Images\\Tank.png", 0, 0);
	enemy = new GameObject("Images\\Bullet.png", 50, 50);
	map = new Map();
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

	map->DrawMap();
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
