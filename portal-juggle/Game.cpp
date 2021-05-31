#include "Game.h"
#include <random>
#include <chrono>
#include <math.h>

SDL_Renderer* Game::renderer = nullptr;

GameObject topPaddle, botPaddle;

Ball ball;
Portal topPortal, botPortal;

float RealRandomNumber(float min, float max) {
	std::uniform_real_distribution<float> distribution(min, max);
	std::random_device rd;
	std::default_random_engine generator(rd());
	return distribution(generator);
}

Game::Game() {
	window = NULL;
	renderer = NULL;
	start = false;
	quit = false;
	SDL_Init(SDL_INIT_EVERYTHING);

	//PADDLES//
	topPaddle.Size(100, 10);
	botPaddle.Size(100, 10);

	topPaddle.Color(0, 0, 255, 255);
	botPaddle.Color(255, 0, 0, 255);

	topPaddle.Position(WIDTH / 4 - topPaddle.w / 2, HEIGHT / 2 - topPaddle.h / 2 - 30);
	botPaddle.Position(3 * WIDTH / 4 - botPaddle.w / 2, HEIGHT / 2 - botPaddle.h / 2 + 30);

	//BALL//
	ball.Size(10);
	ball.Position(topPaddle.position.x + topPaddle.w / 2 - ball.R / 2, topPaddle.position.y - ball.R);

	//PORTALS//
	topPortal.Size(20, 300);
	botPortal.Size(20, 300);

	topPortal.Color(255, 0, 0, 255);
	botPortal.Color(0, 0, 255, 255);

	topPortal.Position(WIDTH / 2 - topPortal.w / 2, 100);
	botPortal.Position(WIDTH / 2 - botPortal.w / 2, 400);

	//MIDLINE//
	midLine.w = WIDTH;
	midLine.h = 5;
	midLine.x = 0;
	midLine.y = HEIGHT / 2 - midLine.h / 2;

	float minRange = (float)WIDTH / 2 + 60.0f - (topPaddle.position.x + topPaddle.w / 2);
	float maxRange = (float)WIDTH - 60.0f - (topPaddle.position.x + topPaddle.w / 2);

	float range = RealRandomNumber(minRange, maxRange) / 60.0f;
	std::cout << range << std::endl;

	float angle = RealRandomNumber(3.1415f / 4.0f, 3.1415f / 3.0f);
	std::cout << angle << std::endl;

	float v0Sqrd = g * range / sin(2 * angle);
	float v0 = sqrt(v0Sqrd);

	std::cout << v0 << std::endl;

	ballVx = v0 * cos(angle);
	ballVy = -v0 * sin(angle);
}

void Game::Init() {
	window = SDL_CreateWindow("Portal Juggle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, NULL);
	renderer = SDL_CreateRenderer(window, -1, 0);
}

void Game::Events() {
	SDL_Event e;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT)
			quit = true;
	}

	if (keystates[SDL_SCANCODE_D]) {
		if (!start)
			start = true;

		topPaddle.position.x += 10;
		botPaddle.position.x -= 10;
	}
	if (keystates[SDL_SCANCODE_A]) {
		if (!start)
			start = true;

		topPaddle.position.x -= 10;
		botPaddle.position.x += 10;
	}
}

void Game::Reset() {
	start = false;

	g = abs(g);

	topPaddle.position.x = WIDTH / 4 - topPaddle.w / 2;
	botPaddle.position.x = 3 * WIDTH / 4 - botPaddle.w / 2;

	ball.position.x = topPaddle.position.x + topPaddle.w / 2 - ball.R / 2;
	ball.position.y = topPaddle.position.y - ball.R;

	float minRange = (float)WIDTH / 2 + 60.0f - (topPaddle.position.x + topPaddle.w / 2);
	float maxRange = (float)WIDTH - 60.0f - (topPaddle.position.x + topPaddle.w / 2);

	float range = RealRandomNumber(minRange, maxRange) / 60.0f;
	std::cout << "Range = " << range << std::endl;

	float angle = RealRandomNumber(3.1415f / 4.0f, 3.1415f / 3.0f);
	std::cout << "Angle = " << angle << std::endl;

	float v0Sqrd = g * range / sin(2 * angle);
	float v0 = sqrt(v0Sqrd);

	std::cout << "Speed = " << v0 << std::endl;
	ballVx = v0 * cos(angle);
	ballVy = -v0 * sin(angle);

	ball.Velocity(ballVx, ballVy);
}

void Game::Update() {
	if (start) {
		ball.velocity.y += g * 0.02f;
		ball.position.y += (ball.velocity.y * 0.02f + 0.5f * g * 0.02f * 0.02f) * 60;
		ball.position.x += ball.velocity.x * 0.02f * 60;

		std::cout << ball.position.y << std::endl;

		if (SDL_HasIntersection(&ball.rect, &midLine))
			Reset();

		if (SDL_HasIntersection(&ball.rect, &topPortal.rect)) {
			float deltaY = HEIGHT / 2 - ball.position.y;
			ball.position.x = topPortal.position.x + topPortal.w;
			ball.position.y += 2 * deltaY + ball.R;
			ball.velocity.y = -ball.velocity.y;
			g = -g;
			std::cout << "Ball teleported!" << std::endl;
		}

		if (SDL_HasIntersection(&ball.rect, &botPortal.rect)) {
			float deltaY = ball.position.y - HEIGHT / 2;
			ball.position.x = botPortal.position.x - ball.R;
			ball.position.y -= 2 * deltaY - ball.R;
			ball.velocity.y = -ball.velocity.y;
			g = -g;
			std::cout << "Ball teleported!" << std::endl;
		}

		if (SDL_HasIntersection(&ball.rect, &topPaddle.destRect)) {
			std::cout << "Top paddle hit" << std::endl;

			ball.position.y = topPaddle.position.y - ball.R;

			float minRange = (float)WIDTH / 2 + 60.0f - (ball.position.x + ball.R / 2);
			float maxRange = (float)WIDTH - 60.0f - (ball.position.x + ball.R / 2);

			float range = RealRandomNumber(minRange, maxRange) / 60.0f;
			std::cout << "Range = " << range << std::endl;

			float angle = RealRandomNumber(3.1415f / 4.0f, 3.1415f / 3.0f);
			std::cout << "Angle = " << angle << std::endl;

			float v0Sqrd = g * range / sin(2 * angle);
			float v0 = sqrt(v0Sqrd);

			std::cout << "Speed = " << v0 << std::endl;

			ballVx = v0 * cos(angle);
			ballVy = -v0 * sin(angle);

			ball.Velocity(ballVx, ballVy);
		}

		if (SDL_HasIntersection(&ball.rect, &botPaddle.destRect)) {
			std::cout << "Bot paddle hit" << std::endl;

			ball.position.y = botPaddle.position.y + botPaddle.h;

			float minRange = (float)(ball.position.x + ball.R / 2) - (float)(WIDTH / 2 - 60);
			float maxRange = (float)(ball.position.x + ball.R / 2) - 60;

			float range = RealRandomNumber(minRange, maxRange) / 60.0f;
			std::cout << "Range = " << range << std::endl;

			float angle = RealRandomNumber(3.1415f / 4.0f, 3.1415f / 3.0f);
			std::cout << "Angle = " << angle << std::endl;

			float v0Sqrd = abs(g * range / sin(2 * angle));
			float v0 = sqrt(v0Sqrd);

			std::cout << "Speed = " << v0 << std::endl;

			ballVx = -v0 * cos(angle);
			ballVy = v0 * sin(angle);

			ball.Velocity(ballVx, ballVy);
		}
	}

	ball.Update();
	topPaddle.Update();
	botPaddle.Update();
	topPortal.Update();
	botPortal.Update();
}

void Game::Render() {
	//clear window
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	//RENDER NEW STUFF//

	//midline
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &midLine);

	//ball
	ball.Render();

	//paddles
	topPaddle.Render();
	botPaddle.Render();

	//portals
	topPortal.Render();
	botPortal.Render();

	//update renderer
	SDL_RenderPresent(renderer);
}

bool Game::GetGameState() {
	return quit;
}

void Game::Exit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}