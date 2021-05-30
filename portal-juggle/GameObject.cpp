#include "GameObject.h"

GameObject::GameObject() {
	w = h = 20;
	position.x = position.y = 0;
	velocity.x = velocity.y = 0;

	srcRect.w = srcRect.h = srcRect.x = srcRect.y = 0;

	destRect.w = w;
	destRect.h = h;
	destRect.x = position.x;
	destRect.y = position.y;
}

void GameObject::Size(int width, int height) {
	w = width;
	h = height;
}

void GameObject::AddSprite(const char* filename) {
	surface = IMG_Load(filename); 
	srcRect.w = surface->w;
	srcRect.h = surface->h;
	texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
}

void GameObject::Render() {
	SDL_RenderCopy(Game::renderer, texture, &srcRect, &destRect);
}

void GameObject::Update() {
	destRect.w = w;
	destRect.h = h;
	destRect.x = position.x;
	destRect.y = position.y;
}