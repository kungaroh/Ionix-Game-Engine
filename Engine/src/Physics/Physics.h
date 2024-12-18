#pragma once 

#include <b2_world.h>
#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_circle_shape.h>
#include <b2_contact.h>
#include <b2_contact_manager.h>
#include <b2_settings.h>
#include <sstream>

#include "../Logging/Console.h"

#include "Raycasting.h"
//#define TESTING_PHYSICS

namespace IonixEngine
{
	constexpr float physicsScale = 0.025f;
	constexpr float iPhysicsScale = 1.0f / physicsScale;

	

	class IonixContactListener :public b2ContactListener
	{
		void BeginContact(b2Contact* contact);

		void EndContact(b2Contact* contact);
	};

	class Physics
	{
		b2World *m_pWorld;
		IonixContactListener m_contactListenerInstance;
		Raycasting m_raycastingInstance;
	public:
		Physics(float gravX, float gravY);
		void UpdatePhysics(float dt);
		b2World* GetWorld() const { return m_pWorld; }
		Raycasting* getRaycast() { return & m_raycastingInstance;
		; }
		
#ifdef TESTING_PHYSICS

		void TestGravityWorks();

		void TestSetGravityScale(float newGrav);

		void TestVariableForce();

		void TestColliderType();

		void TestCollisionWorks();
		void TestDestroyWorks();

		// example adding a body to the world
		void TestPhysics()
		{
			///Create shape
			b2BodyDef myBodyDef;
			myBodyDef.type = b2_dynamicBody;

			float gameX, gameY, angle; // position and angle from game object transform
			float w, h; // width and height of box in game world units
			gameX = 100;
			gameY = 100;
			w = h = 100;
			angle = 45.0f;

			myBodyDef.position.Set(gameX * IonixEngine::physicsScale, gameY * IonixEngine::physicsScale); // scale down - physics works better with smaller numbers than pixels
			myBodyDef.angle = angle * 3.1415926f / 180.0f; // box2d uses radians, game uses degrees

			b2Body *m_box2dBody = GetWorld()->CreateBody(&myBodyDef);

			b2PolygonShape shapeBox;
			shapeBox.SetAsBox(w * IonixEngine::physicsScale / 2, h * IonixEngine::physicsScale / 2); //box2d uses half-width, box is centred on the centre of gravity

			b2FixtureDef boxFixtureDef;
			boxFixtureDef.restitution = 0.6f;

			boxFixtureDef.shape = &shapeBox;
			boxFixtureDef.density = 1;
			boxFixtureDef.isSensor = false; // if true this would be a trigger region
			m_box2dBody->CreateFixture(&boxFixtureDef);
			m_box2dBody->GetUserData().pointer = (uintptr_t)nullptr; // suggest this is a pointer to the physics component, can be used by collision callbacks to find the object

			// have now added the body to the world, let's call update a few times and output its position to the console

			for (uint32_t iStep = 0; iStep < 10; iStep++)
			{
				UpdatePhysics(0.016666f);

				float x, y, angle;
				x = m_box2dBody->GetPosition().x * IonixEngine::iPhysicsScale;
				y = m_box2dBody->GetPosition().y * IonixEngine::iPhysicsScale;
				angle = m_box2dBody->GetAngle() * 180.0f / 3.1415926f;

				std::stringstream ss;
				ss << "physics body at " << x << " " << y << " " << angle;

				Console::info(ss.str());
			}

		}
#endif
	};
}