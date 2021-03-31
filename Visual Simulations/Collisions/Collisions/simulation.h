#ifndef SIMULATION_H
#define SIMULATION_H

#include "definitions.h"

class Simulation
{
private:

public:

private:

public:
	Simulation()
	{

	}

	~Simulation() {};

	void Initialize();
	void Update(sf::RenderWindow* window, float dt);
	void Draw(sf::RenderWindow* window);
};

#endif // !SIMULATION_H
