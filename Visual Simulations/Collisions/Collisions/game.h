#ifndef GAME_H
#define GAME_H

#include "definitions.h"
#include "consoleColorizer.h"
#include "inputManager.h"
#include "simulation.h"

class Game
{
private:
	// This is the default font we will use
	sf::Font font;

	Simulation simulation;

public:

private:

	void Initialize();
	void InitializeWindowSettings(sf::RenderWindow* window);
	void InitializeSimulationSettings();

	void CloseGame(sf::RenderWindow* window);

	// All game logic
	void Update(sf::RenderWindow* window, float dt);
	void UpdateInput(sf::RenderWindow* window);

	// All rendering
	void Draw(sf::RenderWindow* window);

public:
	// We will define the constructor and destructor locally in the header file
	Game()
	{
		Initialize();
	}

	~Game() {}

	void Begin();
};

#endif // !GAME_H
