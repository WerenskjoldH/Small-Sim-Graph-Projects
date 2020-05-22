#include "Bot.h"
#include "GFXHelper.h"


void bot::Initialize()
{
	direction = rn::vector3f(0.25, 0.5).unit();

	position = rn::vector3f(250, 250);

	speed = 25.0f;
}

void bot::Update(float dt)
{
	position += speed * direction * dt;

	// Bounds
	if (position.x < 0 || position.x > WINDOW_WIDTH)
	{
		direction.x *= -1;
	}

	if (position.y < 0 || position.y > WINDOW_HEIGHT)
	{
		direction.y *= -1;
	}
}

void bot::Draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 200, 100, 100, 255);
	gfxDrawBrenCircle(renderer, position.x, position.y, 10, true);
}
