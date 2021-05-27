#include "Game.h"

int main(int argc, char** args) {
	Game game;

	double startFrame;
	double endFrame;

	int count = 0;

	game.Init();

	while (!game.GetGameState()) {

		startFrame = SDL_GetTicks();

		game.Events();
		game.Update();
		game.Render();

		endFrame = SDL_GetTicks() - startFrame;

		if (endFrame < 1000.0f / 60.0f) {
			SDL_Delay(1000.0f / 60.0f - endFrame);
		}
	}

	game.Exit();
	return 0;
}