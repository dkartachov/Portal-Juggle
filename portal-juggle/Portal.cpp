#include "Portal.h"

Portal::Portal() {
	w = h = 10;
	r = g = b = a = 255;
	position.x = position.y = 0;

	rect.w = w;
	rect.h = h;
	rect.x = position.x;
	rect.y = position.y;
}

void Portal::Size(int width, int height) {
	w = width;
	h = height;
}

void Portal::Color(int red, int green, int blue, int alpha) {
	r = red;
	b = blue;
	g = green;
	a = alpha;
}

void Portal::Position(int x, int y) {
	position.x = x;
	position.y = y;
}

void Portal::Render() {
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Portal::Update() {
	rect.w = w;
	rect.h = h;
	rect.x = position.x;
	rect.y = position.y;
}