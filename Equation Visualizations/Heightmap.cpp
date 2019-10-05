#include <iostream>

#include <SDL/SDL.h>

#define WINDOW_WIDTH 400
#define WINDOW_HEIGHT 400
#define WINDOW_PIXELS WINDOW_HEIGHT * WINDOW_WIDTH
#define DELTA_TIME 0.1f

#define GET_X_POS(i) i % WINDOW_WIDTH
#define GET_Y_POS(i) int(float(i)/float(WINDOW_WIDTH))

#define GET_INDEX(x, y) int(x + y * WINDOW_WIDTH)

// Measure values from 0 to 1
float map[WINDOW_PIXELS];

SDL_Window* window;
SDL_Renderer* renderer;

int curVisualization = 4;
int prevVisualization = curVisualization;

bool isRunning = 1;
bool mouseDown = 0;
bool prevMouseState = mouseDown;

float iTime = 0.f;

float mouseX = 0.f;
float mouseY = 0.f;

void update();

void draw();

void paint(int x, int y, float strength);

inline int safeGetIndex(int x, int y)
{
	if (GET_INDEX(x, y) < 0 || GET_INDEX(x, y) > WINDOW_HEIGHT * WINDOW_WIDTH)
	{
		printf("ERROR::OUT OF BOUNDS::Attempt to access out of bounds map array index");
		return 0;
	}
	else
		return GET_INDEX(x, y);
}

void resetMap()
{
	for (int i = 0; i < WINDOW_PIXELS; i++)
		map[i] = 1.f;

	printf("World heightmap set to default: All values 1.f\n");
}

int main(int args, char* argv[])
{
	resetMap();

	// Create Window and Begin
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		std::cout << "Subsystems Initialized" << std::endl;
	else
	{
		std::cout << "ERROR::FATAL::Subsystems FAILED to initalize" << std::endl;
		isRunning = false;
	}

	window = SDL_CreateWindow("Visualizations - Hunter Werenskjold", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window)
		std::cout << "Window Created" << std::endl;
	else
	{
		std::cout << "ERROR::FATAL::Window FAILED to be created" << std::endl;
		isRunning = false;
	}



	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer)
	{
		std::cout << "Renderer Created" << std::endl;
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	}
	else
	{
		std::cout << "ERROR::FATAL::Subsystems FAILED to be created" << std::endl;
		isRunning = false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_Event e;
	while (isRunning)
	{
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				isRunning = false;
			}

			if (e.type == SDL_MOUSEBUTTONDOWN)
				if (e.button.button == SDL_BUTTON_LEFT)
					mouseDown = 1;

			if(e.type == SDL_MOUSEBUTTONUP)
				if(e.button.button == SDL_BUTTON_LEFT)
					mouseDown = 0;

			prevMouseState = mouseDown;

			if (e.type == SDL_MOUSEMOTION)
			{
				mouseX = e.motion.x;
				mouseY = e.motion.y;
			}


			if (e.type == SDL_KEYDOWN)
				if (e.key.keysym.sym == SDLK_0)
					curVisualization = 0;
				else if (e.key.keysym.sym == SDLK_1)
					curVisualization = 1;
				else if (e.key.keysym.sym == SDLK_2)
					curVisualization = 2;
				else if (e.key.keysym.sym == SDLK_3)
					curVisualization = 3;
				else if (e.key.keysym.sym == SDLK_4)
					curVisualization = 4;
				else if (e.key.keysym.sym == SDLK_5)
					curVisualization = 5;
		}

		update();

		draw();
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

void update()
{

	if (curVisualization == 0)
	{
		for (int i = 0; i < WINDOW_PIXELS; i++)
		{
			map[i] = 0.5 * sinf(iTime + sqrtf(((GET_X_POS(i) * GET_X_POS(i)) + (GET_Y_POS(i) * GET_Y_POS(i) + 1.f))) + 1.f);
		}

		iTime += DELTA_TIME;
	}
	else if (curVisualization == 1)
	{
		for (int i = 0; i < WINDOW_PIXELS; i++)
		{
			map[i] = 0.5 * std::fmaxf(sinf(iTime + sqrtf(GET_X_POS(i) + GET_Y_POS(i))) + 1.f +  0.0001f * sqrtf(powf(mouseX - GET_X_POS(i), 2.f) + powf(mouseY - GET_Y_POS(i), 2.f)), 1.f);
		}

		iTime += DELTA_TIME;
	}
	else if (curVisualization == 2)
	{
		for (int i = 0; i < WINDOW_PIXELS; i++)
		{
			map[i] = 0.5 * sinf(iTime + sqrtf(GET_X_POS(i)*100.f + GET_Y_POS(i) * GET_Y_POS(i))) + 1.f;
		}

		iTime += DELTA_TIME;
	}
	else if (curVisualization == 3)
	{
		for (int i = 0; i < WINDOW_PIXELS; i++)
		{
			map[i] = 0.5 * sinf(iTime + 50.f / sqrtf(powf(mouseX - GET_X_POS(i) + 1.f, 2.f) * 100.f + powf(mouseY -  GET_Y_POS(i), 2.f))) + 1.f;
		}

		iTime += DELTA_TIME;
	}
	else if (curVisualization == 4)
	{
		if (prevVisualization != curVisualization)
			resetMap();

		if(mouseDown)
			paint(mouseX, mouseY, 10.f);

		for (int i = 0; i < WINDOW_PIXELS; i++)
		{
			if (map[i] == 1.f)
				continue;
			else if (map[i] > 1.f)
				map[i] = 1.f;
			else if (map[i] < 0.f)
				map[i] = 0.f;
			else
			{
				map[i] += 0.01f;
				if (map[i] >= 1.f)
					map[i]= 1.f;
			}
		}

		iTime += DELTA_TIME;
	}
	else if (curVisualization == 5)
	{
		if (prevVisualization != curVisualization)
			resetMap();

		for (int i = 1; i < WINDOW_PIXELS; i++)
		{

			map[i] = sqrtf(0.005f * iTime * powf(mouseX - GET_X_POS(i), 2.f) + 0.005f * iTime * -1 * powf(WINDOW_HEIGHT/1.75 - GET_Y_POS(i), 5.f));

			//if (mouseDown)
			//{
			//	map[i] *= 0.009f * expf(sqrtf(powf(mouseX - GET_X_POS(i),2.f) + powf(mouseY - GET_Y_POS(i),2.f)));
			//}
		}

		iTime += DELTA_TIME;
	}

	prevVisualization = curVisualization;
}

void draw()
{

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	for (int i = 0; i < WINDOW_PIXELS; i++)
	{
		SDL_SetRenderDrawColor(renderer, 255.f*map[i], 255.f * map[i], 255.f * map[i], 255);
		SDL_RenderDrawPoint(renderer, i%WINDOW_WIDTH, int(float(i)/float(WINDOW_WIDTH)));
	}

	SDL_RenderPresent(renderer);

}

void paint(int x, int y, float strength)
{
	for (int i = 0; i < WINDOW_PIXELS; i++)
	{
		float d = fabsf(sqrtf(powf(float(GET_X_POS(i) - x),2.f) + powf(float(GET_Y_POS(i) - y), 2.f)));
		if (d < strength)
		{
			map[i] -= expf(d);
			if (map[i] < 0.f)
				map[i] -= 0.08f;
		}
	}
}