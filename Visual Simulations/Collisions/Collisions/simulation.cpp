#include "simulation.h"

void Simulation::AddEntity(sf::Vector2f _position)
{
	entities.push_back(new Entity(_position));
}

void Simulation::AddEntity(sf::Vector2i _position)
{
	AddEntity(sf::Vector2f(_position.x, _position.y));
}

bool Simulation::CalculateCollisionOffset(Entity* a, Entity* b, sf::Vector2f translateAToB, sf::Vector2f* offset)
{
	
	float magTranslateAToB = sqrtf(translateAToB.x * translateAToB.x + translateAToB.y * translateAToB.y);

	sf::Vector2f aToB = b->GetPosition() - a->GetPosition();

	// Get distance between circles
	float distBetween = sqrtf(aToB.x * aToB.x + aToB.y * aToB.y);
	float magVelocity = magTranslateAToB;

	///
	// Escape Tests
	///

	// Is the current velocity magnitude greater or equal to the distance between the circles minus the radius of both
	if (magVelocity < distBetween - (a->GetRadius() + b->GetRadius()))
		false;

	float e1DotE2 = a->GetPosition().x * b->GetPosition().x + a->GetPosition().y * b->GetPosition().y;

	// Is Entity One moving towards Entity Two
	if (e1DotE2 <= 0)
		false;

	sf::Vector2f velocityNorm = translateAToB / magVelocity;
	float normDotAToB = velocityNorm.x * aToB.x + velocityNorm.y * aToB.y;

	float closestDistance = distBetween * distBetween - normDotAToB * normDotAToB;

	if (closestDistance > powf(a->GetRadius() + b->GetRadius(), 2.0f))
		false;

	if (distBetween > magVelocity)
		false;

	float collisionPointAlongV = powf((a->GetRadius() + b->GetRadius()), 2.0f) - closestDistance;

	float distToCollision = closestDistance - sqrtf(collisionPointAlongV);
	
	sf::Vector2f offsetToCollision = velocityNorm * distToCollision;
	float magOffsetToCollision = sqrtf(offsetToCollision.x * offsetToCollision.x + offsetToCollision.y * offsetToCollision.y);

	offset->x = offsetToCollision.x;
	offset->y = offsetToCollision.y;

	return true;
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



		///
		// Collision will occur
		///

		sf::Vector2f aVel = e->GetVelocity();
		sf::Vector2f bVel = (*it)->GetVelocity();

		sf::Vector2f translateAToB = (*it)->GetVelocity() - e->GetVelocity();
		float magTranslateAToB = sqrtf(translateAToB.x * translateAToB.x + translateAToB.y * translateAToB.y);

		sf::Vector2f translateBToA = e->GetVelocity() - (*it)->GetVelocity();
		float magTranslateBToA = sqrtf(translateBToA.x * translateBToA.x + translateBToA.y + translateBToA.y);

		sf::Vector2f offset;
		
		if (!CalculateCollisionOffset(e, (*it), translateAToB, &offset))
			continue;

		float magOffset = sqrtf(offset.x * offset.x + offset.y * offset.y);
		float shortenedByTranslated = magOffset / magTranslateAToB;

		e->SetPosition(e->GetPosition() + aVel * shortenedByTranslated);
		aVel *= shortenedByTranslated;

		CalculateCollisionOffset((*it), e, translateBToA, &offset);

		magOffset = sqrtf(offset.x * offset.x + offset.y * offset.y);
		shortenedByTranslated = magOffset / magTranslateAToB;

		(*it)->SetPosition((*it)->GetPosition() + bVel * shortenedByTranslated);
		bVel *= shortenedByTranslated;

		///
		// Apply Collision Force
		///

		sf::Vector2f norm = e->GetPosition() - (*it)->GetPosition();
		norm = norm / sqrtf(norm.x * norm.x + norm.y * norm.y);

		float a1 = e->GetVelocity().x * norm.x + e->GetVelocity().y * norm.y;
		float a2 = (*it)->GetVelocity().x * norm.x + (*it)->GetVelocity().y * norm.y;

		float optiP = (2.0 * (a1 - a2)) / (e->GetMass() + (*it)->GetMass());

		sf::Vector2f v1P = aVel + optiP * (*it)->GetMass() * norm;
		sf::Vector2f v2P = bVel + optiP * e->GetMass() * norm;

		e->SetVelocity(v1P);
		(*it)->SetVelocity(v2P);
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
