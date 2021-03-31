#ifndef SIMULATION_H
#define SIMULATION_H

#include "definitions.h"

#include <vector>

class Entity
{
private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;

	float mass;

public:
	Entity(sf::Vector2f _position, float _radius = DEFAULT_RADIUS, float _mass = DEFAULT_MASS, sf::Color _color = DEFAULT_COLOR)
	{
		float radius = shape.getRadius();
		shape.setPosition(sf::Vector2f(_position.x - _radius, _position.y - _radius));
		shape.setOrigin(sf::Vector2f(.5f, .5f));

		shape.setFillColor(_color);
		shape.setRadius(_radius);

		velocity = sf::Vector2f(0, 0);

		mass = _mass;
	}
	virtual ~Entity() {}

	const sf::Color GetColor() const
	{
		return shape.getFillColor();
	}

	void SetColor(sf::Color _color)
	{
		shape.setFillColor(_color);
	}

	const sf::Vector2f GetPosition() const
	{
		return shape.getPosition();
	}

	void SetPosition(sf::Vector2f _position)
	{
		shape.setPosition(_position);
	}

	void SetPosition(sf::Vector2i _position)
	{
		SetPosition(sf::Vector2f(_position.x, _position.y));
	}

	const sf::Vector2f GetVelocity() const
	{
		return velocity;
	}

	void SetVelocity(sf::Vector2f _velocity)
	{
		velocity = _velocity;
	}

	const sf::Vector2f GetAcceleration() const
	{
		return acceleration;
	}

	void SetAcceleration(sf::Vector2f _acceleration)
	{
		acceleration = _acceleration;
	}

	void SetAcceleration(float v)
	{
		acceleration = sf::Vector2f(v, v);
	}

	const float GetRadius() const
	{
		return shape.getRadius();
	}

	void SetRadius(float _radius)
	{
		shape.setRadius(_radius);
	}

	const float GetMass() const
	{
		return mass;
	}

	void SetMass(float _mass)
	{
		mass = _mass;
	}

	const sf::CircleShape GetShape() const
	{
		return shape;
	}
};

class Simulation
{
private:
	std::vector<Entity*> entities;

	sf::Vector2f gravity;

public:

private:
	void AddEntity(sf::Vector2f _position);
	void AddEntity(sf::Vector2i _position);

	void CalculateForces(Entity* e, float dt);
	void Integration(Entity* e, float dt);

public:
	Simulation()
	{
		Initialize();
	}

	~Simulation() 
	{
		// I do this here, but nowhere else as it's the first occurance and I just want to display what 'auto' is in the later loops
		for (std::vector<Entity*>::iterator it = entities.begin(); it != entities.end(); it++)
			delete (*it);
	}

	void Initialize();
	void Update(sf::RenderWindow* window, float dt);
	void Draw(sf::RenderWindow* window);
};

#endif // !SIMULATION_H
