#include "Physics.h"
#include "../EventSystem/Event.h"
#include "Architecture/Application.h"
#include "../Components/PhysicsComponent.h"

namespace IonixEngine
{
	Physics::Physics(float gravX, float gravY)
	{
		m_pWorld = new b2World(b2Vec2(gravX, gravY));
		m_pWorld->SetContactListener(&m_contactListenerInstance);
		m_raycastingInstance = Raycasting(m_pWorld);
	}

	void Physics::UpdatePhysics(float dt)
	{
		m_pWorld->Step(dt, 8, 3);
	}

	void IonixContactListener::BeginContact(b2Contact* contact)
	{
		//Get colliders
		b2BodyUserData bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		b2BodyUserData bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		bodyUserData* b1 = (bodyUserData*)bodyUserDataA.pointer;
		bodyUserData* b2 = (bodyUserData*)bodyUserDataB.pointer;
		bodyUserDataB.pointer;
		uint32_t objId1, objId2; // get these from the body use data somehow - TODO

		objId1 = b1->bodyID;
		objId2 = b2->bodyID;


		if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
		{
			Event_OnTriggerEnter e(objId1, objId2);

			// raise the event
			Application::Get().GetWindow().m_Data.EventCallback(e);
		}
		else
		{
			Event_OnCollisionEnter e(objId1, objId2);

			// raise the event
			Application::Get().GetWindow().m_Data.EventCallback(e);
		}

	}
	void IonixContactListener::EndContact(b2Contact* contact)
	{
		//Get colliders
		b2BodyUserData bodyUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
		b2BodyUserData bodyUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

		bodyUserData* b1 = (bodyUserData*)bodyUserDataA.pointer;
		bodyUserData* b2 = (bodyUserData*)bodyUserDataB.pointer;
		bodyUserDataB.pointer;
		uint32_t objId1, objId2; // get these from the body use data somehow

		objId1 = b1->bodyID;
		objId2 = b2->bodyID;


		if (contact->GetFixtureA()->IsSensor() || contact->GetFixtureB()->IsSensor())
		{
			Event_OnTriggerExit e(objId1, objId2);

			// raise the event
			Application::Get().GetWindow().m_Data.EventCallback(e);
		}
		else
		{
			Event_OnCollisionExit e(objId1, objId2);

			// raise the event
			Application::Get().GetWindow().m_Data.EventCallback(e);
		}
	}
	
#ifdef TESTING_PHYSICS

	void Physics::TestGravityWorks()
	{
		PhysicsComponent* physicsComp = new PhysicsComponent(0, 0, 10, 10, false, 0);
		//physicsComp->SetMass(1000.0f);
		physicsComp->AddForce(b2Vec2(1.0f, 1.0f), b2Vec2(1.0f, 1.0f));
		//while(true)
		for (int i = 0; i < 100; i++)
		{
			physicsComp->OnUpdate(0.016666f);

		}
	}

	void Physics::TestSetGravityScale(float newGrav)
	{
		PhysicsComponent* physicsComp = new PhysicsComponent(0, 0, 10, 10, false, 1);
		PhysicsComponent* physicsComp22222 = new PhysicsComponent(20, 0, 10, 10, false, 2);
		physicsComp->SetGravityScale(newGrav);

		for (int i = 0; i < 100; i++)
		{
			UpdatePhysics(0.016666f);
			physicsComp->OnUpdate(0.016666f);
		}
	}
	
	void Physics::TestVariableForce()
	{
		PhysicsComponent* physicsComp = new PhysicsComponent(0, 0, 10, 10, false, 1);
		physicsComp->SetGravityScale(1);
		physicsComp->AddForce(b2Vec2(1.5f, 2.0f), b2Vec2_zero);

		for (int i = -50; i < 50; i++)
		{
			if (i%10==0)
				physicsComp->AddForce(b2Vec2(-i*10.0f, i*-10.5f), b2Vec2_zero);
			UpdatePhysics(0.016666f);
			physicsComp->OnUpdate(0.016666f);
		}
	}

	void Physics::TestColliderType()
	{
		PhysicsComponent* testPhysicsComp = new PhysicsComponent(0, 50, 10, 10, false, 3);
		testPhysicsComp->AddBoxCollider(0, 0, 15, 15, true);
	}

	void Physics::TestCollisionWorks()
	{
		/* this tests collision by creating two bodies, adding velocity to one of them and checking it collides with the other body
		   (when it collides, the BeginContact function prints a string to the console saying that it was called) */

		   //make 2 physics components and a ground box to use in physics test functions
		float xPos1 = 0.0f, yPos1 = 0.0f, h1 = 10.0f, w1 = 10.0f;
		float xPos2 = 20.0f, yPos2 = 0.0f, h2 = 10.0f, w2 = 10.0f;
		float groundPosX = -10.0f, groundPosY = 30.0f, groundH = 10.0f, groundW = 50.0f;

		PhysicsComponent* physComp1 = new PhysicsComponent(xPos1, yPos1, w1, h1, false, 1);
		PhysicsComponent* physComp2 = new PhysicsComponent(xPos2, yPos2, w2, h2, false, 2);
		PhysicsComponent* groundPhysComp = new PhysicsComponent(groundPosX, groundPosY, groundW, groundH, true, 3);

		//add force so physComp1 moves to the right, towards physicsComp2
		Application::Get().physComp1->AddForce(b2Vec2(1.0f, 0.0f), b2Vec2(0.0f, 0.0f)); //forcePos is 0,0 because it's relative to the centre of the body (force coming from centre)

		for (int i = 0; i < 100; i++)
		{
			UpdatePhysics(0.016666f);
			Application::Get().physComp1->OnUpdate(0.016666f);
			Application::Get().physComp2->OnUpdate(0.016666f);
			Application::Get().groundPhysComp->OnUpdate(0.016666f);

		}
	}


	void Physics::TestDestroyWorks()
	{
		/* Create some physics components using new
			update world a bit
			delete one using delete keyword
			update world a bit
			see if it works
		*/

		//make 2 physics components and a ground box to use in physics test functions
		float xPos1 = 0.0f, yPos1 = 0.0f, h1 = 10.0f, w1 = 10.0f;
		float xPos2 = 20.0f, yPos2 = 0.0f, h2 = 10.0f, w2 = 10.0f;
		float groundPosX = -10.0f, groundPosY = 30.0f, groundH = 10.0f, groundW = 50.0f;

		PhysicsComponent* physComp1 = new PhysicsComponent(xPos1, yPos1, w1, h1, false, 1);
		PhysicsComponent* physComp2 = new PhysicsComponent(xPos2, yPos2, w2, h2, false, 2);
		PhysicsComponent* groundPhysComp = new PhysicsComponent(groundPosX, groundPosY, groundW, groundH, true, 3);

		for (int i = 0; i < 50; i++)
		{
			UpdatePhysics(0.016666f);
			Application::Get().physComp1->OnUpdate(0.016666f);
			Application::Get().physComp2->OnUpdate(0.016666f);
			Application::Get().groundPhysComp->OnUpdate(0.016666f);
		}

		delete Application::Get().physComp1;

		for (int i = 0; i < 50; i++)
		{
			UpdatePhysics(0.016666f);
			Application::Get().physComp1->OnUpdate(0.016666f);
			Application::Get().physComp2->OnUpdate(0.016666f);
			Application::Get().groundPhysComp->OnUpdate(0.016666f);
		}
	}
#endif
}

