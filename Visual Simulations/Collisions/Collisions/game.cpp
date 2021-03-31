#include "game.h"

void Game::Initialize()
{
	InitializeSimulationSettings();

	// Setup Keyboard
	IM.addKey(sf::Keyboard::Space);
	IM.addKey(sf::Keyboard::A);
	IM.addKey(sf::Keyboard::S);
	IM.addKey(sf::Keyboard::D);

}

void Game::InitializeWindowSettings(sf::RenderWindow* window)
{
	window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Collisions - Hunter Werenskjold", sf::Style::Titlebar | sf::Style::Close);

	// It's best to restrict framerate incase any physics gets tied to it
	window->setFramerateLimit(60);
}

void Game::InitializeSimulationSettings()
{

}

void Game::CloseGame(sf::RenderWindow* window)
{

	ConsoleColorizer::getInstance().SetTextColor(FONT_MAGENTA);
	printf("\n\n+================================================+\n");
	printf("\t\t  Closing Game\n");
	printf("+================================================+\n\n");
	ConsoleColorizer::getInstance().SetTextColor();

	window->close();
}

void Game::Begin()
{
	/// Initializations

	// The render window that all data will be written to
	sf::RenderWindow window;

	InitializeWindowSettings(&window);

	// This will be used to track delta time between frames
	sf::Clock clock;

	/// Game Loop Logic

	// This is the Game Loop
	while (window.isOpen())
	{
		sf::Event e;

		// While there are events in queue
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}

			IM.krUpdate(e);
		}

		sf::Time elapsed = clock.restart();

		Update(&window, elapsed.asSeconds());

		window.clear(BACKGROUND_COLOR);

		Draw(&window);

		window.display();

		IM.stateUpdate(&window);
	}
}

void Game::UpdateInput(sf::RenderWindow* window)
{
	if (IM.keyRelease(sf::Keyboard::Escape))
		CloseGame(window);

}

void Game::Update(sf::RenderWindow* window, float dt)
{
	UpdateInput(window);
}

void Game::Draw(sf::RenderWindow* window)
{

}