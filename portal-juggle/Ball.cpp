#include "Ball.h"

Ball::Ball() {
	R = 10;
	r = g = b = a = 255;
	position.x = position.y = 0;
	velocity.x = velocity.y = 0;

	rect.w = rect.h = R;
	rect.x = position.x;
	rect.y = position.y;
}

void Ball::Size(int radius) {
	R = radius;
}

void Ball::Color(int red, int green, int blue, int alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

void Ball::Position(float x, float y) {
	position.x = x;
	position.y = y;
}

void Ball::Velocity(float vx, float vy) {
	velocity.x = vx;
	velocity.y = vy;
}

void Ball::Render() {
	SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
	SDL_RenderFillRect(Game::renderer, &rect);
}

void Ball::Update() {
	rect.w = rect.h = R;
	rect.x = position.x;
	rect.y = position.y;
}