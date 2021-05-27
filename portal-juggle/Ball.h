#pragma once
#include "Game.h"
#include "Vector2D.h"

class Ball {
public:
	int R;
	Vector2D position, velocity;
	SDL_Rect rect;
	Ball();
	void Size(int radius);
	void Color(int r, int g, int b, int a);
	void Position(float x, float y);
	void Velocity(float x, float y);
	void Render();
	void Update();
private:
	int r, g, b, a;
};