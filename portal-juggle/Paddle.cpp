#include "Paddle.h"

Paddle::Paddle() {
	w = h = 10;
	r = g = b = a = 255;
	position.x = position.y = 0;

	rect.w = w;
	rect.h = h;
	rect.x = position.x;
	rect.y = position.y;
}

void Paddle::Size(int width, int height) {
	w = width;
	h = height;
}

void Paddle::Color(int red, int green, int blue, int alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

void Paddle::Position(int x, int y) {
	position.x = x;
	position.y = y;
}

void Paddle::Render() {
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Paddle::Update() {
	rect.w = w;
	rect.h = h;
	rect.x = position.x;
	rect.y = position.y;
}