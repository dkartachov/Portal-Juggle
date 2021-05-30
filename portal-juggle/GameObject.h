#pragma once
#include "Game.h"
#include "Vector2D.h"

class GameObject {
public:
	int w, h;
	Vector2D position, velocity;
	SDL_Rect srcRect, destRect;
	GameObject();
	void Size(int width, int height);
	void AddSprite(const char* filename);
	void Render();
	void Update();
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
};