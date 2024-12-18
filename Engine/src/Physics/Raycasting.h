#pragma once

#include <b2_world.h>
#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_circle_shape.h>
#include <b2_contact.h>
#include <b2_contact_manager.h>
#include <b2_settings.h>
#include <vector>

class BoxCastQueryCallback : public b2QueryCallback
{
public:
	std::vector<b2Body*> foundBodies;

	bool ReportFixture(b2Fixture* fixture)
	{
		foundBodies.push_back(fixture->GetBody());
		return true;
	}
};

class Raycasting
{
	b2World* m_pWorld;

public:
	Raycasting() {};
	Raycasting(b2World* world);
	bool Raycast(int startX, int startY, int dirX, int dirY, float length);
	std::vector<int> RaycastHit(int startX, int startY, int dirX, int dirY, float length);
	int FirstRaycastHit(int startX, int startY, int dirX, int dirY, float length);
	std::vector<int> BoxCast(int x, int y, int x2, int y2);
};