// Note: This project is not meant to be impressive, just a good example project

#include "window.h"
#include "Bot.h"
#include "Definitions.h"

static Uint32 next_time;

window* gameWindow;

bot* botOne;

void Init();
void Begin();
void Update();
void Draw();

// This is directly from the SDL2 documentation: https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidetimeexamples.html
// If I decide to revamp this example, I will wrap this all up in a state manager
Uint32 time_left(void)
{
	Uint32 now;

	now = SDL_GetTicks();
	if (next_time <= now)
		return 0;
	else
		return next_time - now;
}

int main(int args, char* argv[])
{
	Init();
	Begin();

	return 0;
}

void Init()
{
	gameWindow = new window("Driving Bot - Hunter Werenskjold", WINDOW_WIDTH, WINDOW_HEIGHT);
	botOne = new bot();
}

void Begin()
{
	SDL_Event e;
	while (gameWindow->checkIfRunning())
	{
		while (SDL_PollEvent(&e))
		{
			if ((e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE))
			{
				gameWindow->stopWindow();
				break;
			}
		}

		if (!gameWindow->checkIfRunning())
			break;

		Update();
		Draw();
		SDL_Delay(time_left());
		next_time += TICK_INTERVAL;
	}
}

void Update()
{
	botOne->Update(DT);
}

void Draw()
{
	SDL_Renderer* renderer = gameWindow->getRenderer();

	botOne->Draw(renderer);

	gameWindow->renderWindow();
}