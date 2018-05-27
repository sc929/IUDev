#include "GameObject.h"
#include "TextureManager.h"


GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objTexture = TextureManager::LoadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

GameObject::~GameObject()
{}

void GameObject::Update()
{
	xpos++;
	ypos++;
	srcRect.h = 47;
	srcRect.w = 95;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.x = xpos;
	destRect.y = ypos;
	destRect.w = srcRect.w * 2;
	destRect.h = srcRect.h * 2;
}

void GameObject::Render()
{
	SDL_RenderCopy(GameStart::renderer, objTexture, &srcRect, &destRect);
}