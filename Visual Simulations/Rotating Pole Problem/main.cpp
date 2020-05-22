#include <iostream>

#include <SDL/SDL.h>

#include "gfxHelper.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define POINT_RADIUS 3
#define NUMBER_OF_POINTS 8

void update();
void draw();
void end();

bool isRunning;

bool pauseSpinning = false;

int curPoint = 0;

SDL_Window* window;
SDL_Renderer* renderer;

static struct line
{
	int cx, cy;
	float angle;
	int curPoint = -1;
	int prevPoint = -1;
} infLine;

// x,y
int points[2 * NUMBER_OF_POINTS];

int main(int args, char* argv[])
{
	isRunning = true;

	// Populate points

	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		points[2*i] = 114.286 * i;
		points[2*i + 1] = i*i*12.2449;
	}

	infLine.cx = 400;
	infLine.cy = 300;
	infLine.angle = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		std::cout << "Subsystems Initialized" << std::endl;
	else
	{
		std::cout << "ERROR::FATAL::Subsystems FAILED to initalize" << std::endl;
		isRunning = false;
	}

	window = SDL_CreateWindow("Spinning Pole - Hunter Werenskjold", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
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

			if(e.type == SDL_MOUSEBUTTONDOWN && infLine.curPoint != curPoint)
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					points[2 * curPoint] = e.motion.x;
					points[2 * curPoint + 1] = e.motion.y;
					curPoint++;
					if (curPoint >= NUMBER_OF_POINTS)
						curPoint = 0;
				}

			//if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
			//	pauseSpinning = 1 - pauseSpinning;
		}

		update();

		draw();
	}

	end();

	return 0;
}

void update()
{

	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		if (i == infLine.prevPoint)
			continue;

		// Check line collision - This feels hefty, but it works
		float pointX = points[2 * i];
		float pointY = points[2 * i + 1];

		if (infLine.cx == pointX && infLine.cy == pointY)
			continue;

		float posX = cos(infLine.angle) * 2 * WINDOW_WIDTH;
		float posY = sin(infLine.angle) * 2 * WINDOW_HEIGHT;

		float x1 = infLine.cx + posX, x0 = infLine.cx - posX;
		float y1 = infLine.cy + posY, y0 = infLine.cy - posY;

		// We can form a quadratic equation
		float a = (x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0);
		float b = 2 * (x1 - x0) * (x0 - pointX) + 2 * (y1 - y0) * (y0 - pointY);
		float c = (x0 - pointX) * (x0 - pointX) + (y0 - pointY) * (y0 - pointY) - POINT_RADIUS * POINT_RADIUS;

		float d = b * b - 4 * a * c;

		// If the discriminant is positive, we know the line and the point are colliding
		if (d >= 0)
		{
			infLine.cx = pointX;
			infLine.cy = pointY;

			infLine.prevPoint = infLine.curPoint;
			infLine.curPoint = i;
			break;
		}
	}

}

float t = 0;
void draw()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

	for (int i = 0; i < NUMBER_OF_POINTS; i++)
	{
		gfxDrawBrenCircle(renderer, points[2*i], points[2*i+1], POINT_RADIUS, true);
	}

	//switch (infLine.curPoint)
	//{
	//case 0:
	//	SDL_SetRenderDrawColor(renderer, 100, 240, 200, 255);
	//	break;
	//case 1:
	//	SDL_SetRenderDrawColor(renderer, 240, 200, 100, 255);
	//	break;
	//case 2:
	//	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	//	break;
	//case 3:
	//	SDL_SetRenderDrawColor(renderer, 80, 150, 90, 255);
	//	break;
	//case 4:
	//	SDL_SetRenderDrawColor(renderer, 20, 50, 200, 255);
	//	break;
	//case 5:
	//	SDL_SetRenderDrawColor(renderer, 212, 101, 200, 255);
	//	break;
	//case 6:
	//	SDL_SetRenderDrawColor(renderer, 90, 220, 90, 255);
	//	break;
	//case 7:
	//	SDL_SetRenderDrawColor(renderer, 220, 220, 250, 255);
	//	break;
	//default:
	//	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	//}
	

	gfxDrawEndlessLine(renderer, infLine.cx, infLine.cy, WINDOW_WIDTH, WINDOW_HEIGHT, infLine.angle);
	if(!pauseSpinning)
		t += 0.00006f;
	infLine.angle = PI * t;

	SDL_RenderPresent(renderer);
}

void end()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}