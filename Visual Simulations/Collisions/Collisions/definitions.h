#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "inputManager.h"

#define WINDOW_WIDTH	1000
#define WINDOW_HEIGHT	1000

#define BACKGROUND_COLOR sf::Color::Black

#define IM InputManager::getInstance()

#define DEFAULT_RADIUS 10.0f
#define DEFAULT_MASS 1.0f
#define DEFAULT_COLOR sf::Color::White

#define GRAVITY_X 0.0f
#define GRAVITY_Y 1.0F

#define BOUND_DAMPENING -0.5f
#define BOUNDARY 50.0f

#define TIME_SCALE_FACTOR 10.0f

#endif