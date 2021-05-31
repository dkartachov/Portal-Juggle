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
	void Color(int red, int green, int blue, int alpha);
	void AddSprite(const char* filename);
	void Position(float x, float y);
	void Velocity(float x, float y);
	void Render();
	void Update();
private:
	SDL_Surface* surface;
	SDL_Texture* texture;
	int r, g, b, a;
	bool hasSprite;
};