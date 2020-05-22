#ifndef BOT_H
#define BOT_H

#include <SDL/SDL.h>

#include "Vector.h"
// This is a bad approach to this problem, a game object manager would be better
#include "Definitions.h"


class bot
{
public:
	bot() { Initialize(); };
	void Update(float dt);
	void Draw(SDL_Renderer* renderer);

	// Exposing everything, for the scope of the project Getters/Setters feel silly
	rn::vector3f position;
	rn::vector3f direction;
	float speed;
	float radius;

private:
	void Initialize();
};

#endif