#include "GameObject.h"

GameObject::GameObject() {
	w = h = 20;
	r = g = b = a = 255;

	position.x = position.y = 0;
	velocity.x = velocity.y = 0;

	srcRect.w = srcRect.h = srcRect.x = srcRect.y = 0;

	destRect.w = w;
	destRect.h = h;
	destRect.x = position.x;
	destRect.y = position.y;

	hasSprite = false;
}

void GameObject::Size(int width, int height) {
	w = width;
	h = height;
}

void GameObject::Color(int red, int green, int blue, int alpha) {
	r = red;
	g = green;
	b = blue;
	a = alpha;
}

void GameObject::AddSprite(const char* filename) {
	hasSprite = true;
	surface = IMG_Load(filename); 
	srcRect.w = surface->w;
	srcRect.h = surface->h;
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
}

void GameObject::Position(float x, float y) {
	position.x = x;
	position.y = y;
}

void GameObject::Velocity(float x, float y) {
	velocity.x = x;
	velocity.y = y;
}

void GameObject::Render() {
	if (hasSprite)
		SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
	else {
		SDL_SetRenderDrawColor(Game::renderer, r, g, b, a);
		SDL_RenderFillRect(Game::renderer, &destRect);
	}
}

void GameObject::Update() {
	destRect.w = w;
	destRect.h = h;
	destRect.x = position.x;
	destRect.y = position.y;
}