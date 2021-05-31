#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "GameObject.h"

class Game {
public:
	static SDL_Renderer* renderer;
	Game();
	void Init();
	void Events();
	void Reset();
	void Update();
	void Render();
	bool GetGameState();
	void Exit();
private:
	float g = 9.81f;
	const int WIDTH = 800;
	const int HEIGHT = 800;
	bool start, quit;
	SDL_Rect midLine;
	float ballVx, ballVy;
	SDL_Window* window;
};