#include "GameStart.h"
#include "TextureManager.h"
#include "Map.h"
#include "Components.h"
#include "Collision.h"

Map* map;
Manager manager;

SDL_Renderer* GameStart::renderer = nullptr;
SDL_Event GameStart::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

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

	map = new Map();

	player.addComponent<TransformComponent>(2);
	player.addComponent<SpriteComponent>("Images\\Tank.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<TransformComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("Images\\Bullet.png");
	wall.addComponent<ColliderComponent>("wall");
}

void GameStart::handleEvents()
{

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void GameStart::update()
{
	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<TransformComponent>().scale = 1;
	}

	//player.getComponent<TransformComponent>().position.Add(Vector2D(3, 1));

	//if (player.getComponent<TransformComponent>().position.x > 100)
	//{
	//	player.getComponent<SpriteComponent>().setTex("Images\\Bullet.png");
	//}
}

void GameStart::render()
{
	SDL_RenderClear(renderer);
	map->DrawMap();
	manager.draw();
	SDL_RenderPresent(renderer);
}

void GameStart::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
