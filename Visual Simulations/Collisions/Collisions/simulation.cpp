#include "simulation.h"

void Simulation::AddEntity(sf::Vector2f _position)
{
	entities.push_back(new Entity(_position));
}

void Simulation::AddEntity(sf::Vector2i _position)
{
	AddEntity(sf::Vector2f(_position.x, _position.y));
}



void Simulation::CalculateForces(Entity* e, float dt)
{
	sf::Vector2f nAcceleration;

	// Forces are re-calculated per-frame
	e->SetAcceleration(0.0f);

	// Handle Collisions - You may notice we sort of integrate here, this is to avoid calculating the collision twice
	//		It would be better to handle this in a bitmask to avoid double collisions, however it's a tad late now
	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		if (e == (*it))
			continue;

		sf::Vector2f aToB = (*it)->GetPosition() - e->GetPosition();

		// Get distance between circles
		float dist = std::sqrtf(aToB.x * aToB.x + aToB.y * aToB.y);
		
		// Check Collision
		if (dist < e->GetRadius() + (*it)->GetRadius())
		{
			float massSum = e->GetMass() + (*it)->GetMass();

			sf::Vector2f c1NVelocity;
			sf::Vector2f c2NVelocity;

			//c1NVelocity.x = (e->GetVelocity().x * (e->GetMass() - (*it)->GetMass()) + 2.0f * (*it)->GetMass() * (*it)->GetVelocity().x) / massSum;
			//c1NVelocity.y = (e->GetVelocity().y * (e->GetMass() - (*it)->GetMass()) + 2.0f * (*it)->GetMass() * (*it)->GetVelocity().y) / massSum;

			c1NVelocity = (e->GetVelocity() * (e->GetMass() - (*it)->GetMass()) + 2.0f * (*it)->GetMass() * (*it)->GetVelocity()) / massSum;

			//c2NVelocity.x = ((*it)->GetVelocity().x * ((*it)->GetMass() - e->GetMass()) + 2.0f * e->GetMass() * e->GetVelocity().x) / massSum;
			//c2NVelocity.y = ((*it)->GetVelocity().y * ((*it)->GetMass() - e->GetMass()) + 2.0f * e->GetMass() * e->GetVelocity().y) / massSum;

			c2NVelocity = ((*it)->GetVelocity() * ((*it)->GetMass() - e->GetMass()) + 2.0f * e->GetMass() * e->GetVelocity()) / massSum;

			e->SetPosition(e->GetPosition() + c1NVelocity * dt);
			(*it)->SetPosition((*it)->GetPosition() + c2NVelocity * dt);
		}
	}

	// Add Gravity
	nAcceleration += gravity;


	e->SetAcceleration(nAcceleration);
}

void Simulation::Integration(Entity* e, float dt)
{
	sf::Vector2f nPosition = e->GetPosition();
	sf::Vector2f nVelocity = e->GetVelocity();
	
	nVelocity += e->GetAcceleration() * dt;
	nPosition += nVelocity * dt;

	// Handle Bounds

	if (nPosition.x >= WINDOW_WIDTH - BOUNDARY)
	{
		nVelocity.x *= BOUND_DAMPENING;
		nPosition.x = WINDOW_WIDTH - BOUNDARY;
	}

	if (nPosition.x < BOUNDARY)
	{
		nVelocity.x *= BOUND_DAMPENING;
		nPosition.x = BOUNDARY;
	}

 	if (nPosition.y >= WINDOW_HEIGHT - BOUNDARY)
	{
		nVelocity.y *= BOUND_DAMPENING;
		nPosition.y = WINDOW_HEIGHT - BOUNDARY;
	}

	if (nPosition.y < BOUNDARY)
	{
		nVelocity.y *= BOUND_DAMPENING;
		nPosition.y = BOUNDARY;
	}

	e->SetVelocity(nVelocity);
	e->SetPosition(nPosition);
}

void Simulation::Initialize()
{
	gravity = sf::Vector2f(GRAVITY_X, GRAVITY_Y);
}

void Simulation::Update(sf::RenderWindow* window, float dt)
{
	if (IM.mousePress(MOUSE_LMB))
		AddEntity(IM.mousePosition());


	for (auto it = entities.begin(); it != entities.end(); it++)
	{
		CalculateForces(*it, dt);
		Integration(*it, dt);
	}

}


void Simulation::Draw(sf::RenderWindow* window)
{

	for (auto it = entities.begin(); it != entities.end(); it++)
		window->draw((*it)->GetShape());
}
