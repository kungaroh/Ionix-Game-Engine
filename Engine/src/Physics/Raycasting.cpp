#pragma once
#include "Raycasting.h"
#include "Components/PhysicsComponent.h"
#include "Architecture/Application.h"

Raycasting::Raycasting(b2World* world)
{
	m_pWorld = world;
}

//checks if raycast between two points intersects any object
//if it does, returns true
bool Raycasting::Raycast(int startX, int startY, int dirX, int dirY, float length)
{
	//creates a b2d raycast thing 
	b2RayCastInput input;
	input.p1 = b2Vec2(startX, startY);
	input.p2 = b2Vec2(dirX, dirY);
	input.maxFraction = length;
	b2RayCastOutput output;

	//loops through every body in the world to check if the raycast has hit any fixtures
	//returns true if it has hit anything
	for (b2Body* b = m_pWorld->GetBodyList(); b; b = b->GetNext()) {
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput output;
			if (!f->RayCast(&output, input, 0))
				continue;
			else
			{
				return true;
			}
		}
	}

	return false;
}

//returns a vector of all the IDs that the raycast has intersected with
std::vector<int> Raycasting::RaycastHit(int startX, int startY, int dirX, int dirY, float length)
{
	std::vector<int> collidingBodiesIDs;

	bool ignore = false, colliding = false;

	//same as function above
	b2RayCastInput input;
	input.p1 = b2Vec2(startX, startY);
	input.p2 = b2Vec2(dirX, dirY);
	input.maxFraction = length;
	b2RayCastOutput output;

	//loops through every body in world, checking if they hit any fixtures
	//gets teh body of the fixture hit and adds it to the list of bodies hit
	//these can then be used later to return what objects have been hit
	for (b2Body* b = m_pWorld->GetBodyList(); b; b = b->GetNext()) {
		colliding = false;
		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput output;
			if (!f->RayCast(&output, input, 0))
				continue;
			else
			{
				colliding = true;
			}
		}
		if (colliding)
		{
			
			b2BodyUserData data = b->GetUserData();
			bodyUserData* bodyData = (bodyUserData*)data.pointer;

			for (int bodyId : collidingBodiesIDs) {
				if (bodyId = bodyData->bodyID) 
				{
					ignore = true;
				}
			}
			if (!ignore) {
				collidingBodiesIDs.emplace_back(bodyData->bodyID);
			}
		}
		ignore = false;
	}

	return collidingBodiesIDs;
}

//returns the id of the first object that is intersected by the raycast
int Raycasting::FirstRaycastHit(int startX, int startY, int dirX, int dirY, float length)
{
	//same as function above
	b2RayCastInput input;
	input.p1 = b2Vec2(startX, startY);
	input.p2 = b2Vec2(dirX, dirY);
	input.maxFraction = length;
	b2RayCastOutput output;

	float closestFraction = length;
	int closestID = NULL;
	for (b2Body* b = m_pWorld->GetBodyList(); b; b = b->GetNext()) {

		for (b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext()) {

			b2RayCastOutput output;
			if (!f->RayCast(&output, input, 0))
				continue;
			if (output.fraction < closestFraction)
			{
				closestFraction = output.fraction;
				b2BodyUserData data = b->GetUserData();
				bodyUserData* bodyData = (bodyUserData*)data.pointer;

				closestID = bodyData->bodyID;
			}
		}

		return closestID;
	}
}

//does a box cast and returns the IDs of all the objects within that area
std::vector<int> Raycasting::BoxCast(int x, int y, int x2, int y2)
{
	bool ignore = false;
	vector<int> bodyIDs;
	BoxCastQueryCallback queryCallback;
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(x, y);
	aabb.upperBound = b2Vec2(x2, y2);
	m_pWorld->QueryAABB(&queryCallback, aabb);
	for (int i = 0; i < queryCallback.foundBodies.size(); i++)
	{
		b2BodyUserData data = queryCallback.foundBodies[i]->GetUserData();
		bodyUserData* bodyData = (bodyUserData*)data.pointer;
		for(int bodyId : bodyIDs) { //checking if a body ID was already added. Could happen if an object has multiple colliders
			if (bodyId == bodyData->bodyID) {
				ignore = true;
			}
		}
		if (!ignore) 
		{
			bodyIDs.push_back(bodyData->bodyID);
		}
		ignore = false;
	}

	return bodyIDs;
}
