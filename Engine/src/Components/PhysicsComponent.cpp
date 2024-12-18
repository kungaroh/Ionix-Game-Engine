#pragma once
#include "PhysicsComponent.h"
#include "TransformComponent.h"
#include "../Logging/Console.h"
#include "../EventSystem/Event.h"
#include "Architecture/Application.h"

// currently using the constructor for the basic setup of the physics component.Will eventually change this however this works for now.Makes a rigidbody with a set shape + density.Colliders dont exist yet

PhysicsComponent::~PhysicsComponent()
{
	m_pWorld->DestroyBody(rigidBody);
}

void PhysicsComponent::OnUpdate(float deltaTime)
{
	TransformComponent* tc = m_owner->GetComponentOfType<TransformComponent>();

	if (isKinematic)
	{
		// force simulation position from game position
		rigidBody->SetTransform(b2Vec2(tc->x * IonixEngine::physicsScale, tc->y * IonixEngine::physicsScale), tc->angle * pi / 180.0f);
		rigidBody->SetAwake(true); // make sure it's awake, velocity will be zero probably
	}
	else
	{
		float x, y, angle;
		x = rigidBody->GetPosition().x * IonixEngine::iPhysicsScale;
		y = rigidBody->GetPosition().y * IonixEngine::iPhysicsScale;
		angle = rigidBody->GetAngle() * 180.0f / pi;

		tc->x = x;
		tc->y = y;
		tc->angle = angle;
	}
}

void PhysicsComponent::OnStart()
{
	IonixEngine::Application& app = IonixEngine::Application::Get();
	//Gets the b2d world to do other physics stuff

	IonixEngine::Physics* physics = app.layerPhysics->GetPhysics();

	m_pWorld = app.layerPhysics->GetPhysics()->GetWorld();

	userData.bodyID = m_owner->UID(); //makes user data which is assigned the ID of the body. Use this to get the ID on collisions

	SetType(isStatic);

	TransformComponent* tc = m_owner->GetComponentOfType<TransformComponent>();
	//sets up the rigid body def (getting position and angle from object transform)
	rigidBodyDef.position.Set(tc->x * IonixEngine::physicsScale, tc->y * IonixEngine::physicsScale);
	rigidBodyDef.angle = tc->angle * pi / 180.0f;

	//creates rigidbody based on world
	rigidBody = m_pWorld->CreateBody(&rigidBodyDef);

	rigidBody->GetUserData().pointer = (uintptr_t)&userData; // suggest this is a pointer to the physics component, can be used by collision callbacks to find the object

	b2PolygonShape shapeBox;
	shapeBox.SetAsBox(w * IonixEngine::physicsScale / 2, h * IonixEngine::physicsScale / 2); //box2d uses half-width, box is centred on the centre of gravity

	b2FixtureDef boxFixtureDef;
	boxFixtureDef.restitution = restitution;


	// HL - 27/11/24 - quick and dirty 'kinematic' objects - make them ignore gravity and have large mass (so everything bounces off them)
	if (isKinematic)
	{
		density = 100000.0f;
		rigidBody->SetGravityScale(0.0f);
	}

	boxFixtureDef.shape = &shapeBox;
	boxFixtureDef.density = density;
	boxFixtureDef.friction = friction;
	//boxFixtureDef.isSensor = false; // if true this would be a trigger region
	if (isTrigger)
	{
		boxFixtureDef.isSensor = true;
	}
	else
	{
		boxFixtureDef.isSensor = false;
	}

	if (lockRotation)
	{
		rigidBody->SetFixedRotation(true);
	}

	auto colData = std::make_shared<colliderUserData>();
	colData->collID = 0;
	colData->collType = BOX;
	//boxFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(bodyData.get());
	boxFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(colData.get());
	colData->relatedFixture = rigidBody->CreateFixture(&boxFixtureDef);
	mColliderUserData.emplace_back(std::move(colData));
	numColliders++;
}
void PhysicsComponent::SetType(bool isStatic)
{
	//For testing, check if we want a static or dynamic body
	if (isStatic)
	{
		rigidBodyDef.type = b2_staticBody;
	}
	else
	{
		rigidBodyDef.type = b2_dynamicBody;
	}
}

//Sets the gravity scale of the physicscomponent, default is 1.0f
void PhysicsComponent::SetGravityScale(float gravScale)
{
	rigidBody->SetGravityScale(gravScale);
}

//Adds a force to the object. forcePos is where it happens in world. If force is placed behind an object, the object will move forward
void PhysicsComponent::AddForce(float forceX, float forceY, float forcePosX, float forcePosY)
{ 
	b2Vec2 force{ forceX,forceY };
	b2Vec2 forcePos{ forcePosX * IonixEngine::physicsScale ,forcePosY * IonixEngine::physicsScale };
	rigidBody->ApplyForce(force, forcePos, true); 
}


// x and y are relative to the rigidBody that its being added to, not world.
//creates a box collider with x, y, width and height. Allows collider to be a trigger / sensor or solid collider

void PhysicsComponent::AddBoxCollider(float posX, float posY, float w, float h, bool isTrigger)
{
	//creates user data for the box fixture. Holds a reference to the collider fixture and what type it is.................
	auto boxData = std::make_shared<colliderUserData>();
	boxData->collID = numColliders;
	numColliders++;
	boxData->collType = BOX;
	//creates box shape
	b2PolygonShape box;
	box.SetAsBox(w * IonixEngine::physicsScale / 2, h * IonixEngine::physicsScale / 2, b2Vec2(posX, posY), 0);


	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &box;

	boxFixtureDef.userData.pointer =  reinterpret_cast<uintptr_t>(boxData.get());
	if (isTrigger)
	{
		boxFixtureDef.isSensor = true;
	}
	else
	{
		boxFixtureDef.isSensor = false;
	}
	//adds collider to rigidBody
	boxData->relatedFixture = rigidBody->CreateFixture(&boxFixtureDef);

	mColliderUserData.emplace_back(std::move(boxData));
	boxData = nullptr;
}


// x and y are relative to the rigidBody that its being added to, not world.
//creates a circle collider with x, y, radius. Allows collider to be a trigger / sensor or solid collider

void PhysicsComponent::AddCircleCollider(float posX, float posY, float radius, bool isTrigger)
{
	//Creates user data for the fixture. This will hold a reference to the fixture and what type it is.
	auto circleData = std::make_shared<colliderUserData>();
	circleData->collID = numColliders;
	numColliders++;
	circleData->collType = CIRCLE;

	//creates a circle shape
	b2CircleShape circle;
	circle.m_p.Set(posX, posY);
	circle.m_radius = radius;

	b2FixtureDef circleFixtureDef;
	circleFixtureDef.userData.pointer = reinterpret_cast<uintptr_t>(circleData.get());
	circleFixtureDef.shape = &circle;

	if (isTrigger)
	{
		circleFixtureDef.isSensor = true;
	}
	else
	{
		circleFixtureDef.isSensor = false;
	}
	//adds collider to rigidBody

	circleData->relatedFixture = rigidBody->CreateFixture(&circleFixtureDef);

	mColliderUserData.emplace_back(std::move(circleData));
	circleData = nullptr;
}

//Removes collider from the body and cleans up other stuff related to the removed fixture
void PhysicsComponent::RemoveCollider(int ID)
{
	for (int i = 0; i < mColliderUserData.size(); i++)
	{
		if (ID == mColliderUserData[i].get()->collID)
		{
			rigidBody->DestroyFixture(mColliderUserData[i].get()->relatedFixture);
			std::swap(mColliderUserData[i], mColliderUserData[mColliderUserData.size() - 1]);
			mColliderUserData.pop_back();
			break;
		}
	}
}

void PhysicsComponent::SetDensity(float density)
{
	for (b2Fixture* f = rigidBody->GetFixtureList(); f; f = f->GetNext()) 
	{
		b2FixtureUserData fixData = f->GetUserData();
		colliderUserData* data = (colliderUserData*)fixData.pointer;
		if(data->collID = 0)
		{
			f->SetDensity(density);
		}
	}
	rigidBody->ResetMassData();
}

void PhysicsComponent::SetRestitution(float restitution)
{
	for (b2Fixture* f = rigidBody->GetFixtureList(); f; f = f->GetNext())
	{
		b2FixtureUserData fixData = f->GetUserData();
		colliderUserData* data = (colliderUserData*)fixData.pointer;
		if (data->collID = 0)
		{
			f->SetRestitution(restitution);
		}
	}
}

void PhysicsComponent::SetFriction(float friction)
{
	for (b2Fixture* f = rigidBody->GetFixtureList(); f; f = f->GetNext())
	{
		b2FixtureUserData fixData = f->GetUserData();
		colliderUserData* data = (colliderUserData*)fixData.pointer;
		if (data->collID = 0)
		{
			f->SetFriction(friction);
		}
	}
}

void PhysicsComponent::SetRotationActive(bool active)
{
	rigidBody->SetFixedRotation(!active);
}

void PhysicsComponent::SetTransform(float x, float y)
{
	rigidBody->SetTransform(b2Vec2(x * IonixEngine::physicsScale, y * IonixEngine::physicsScale), rigidBody->GetAngle());
}

void PhysicsComponent::SetRotation(float degree)
{
	b2Transform transform = rigidBody->GetTransform();
	rigidBody->SetTransform(rigidBody->GetPosition(), degree * pi / 180);
}

void PhysicsComponent::GetVelocity(float& vx, float& vy) 
{
	b2Vec2 vel = rigidBody->GetLinearVelocity();
	vx = vel.x * IonixEngine::iPhysicsScale;
	vy = vel.y * IonixEngine::iPhysicsScale;
}

void PhysicsComponent::SetVelocity(float vx, float vy) 
{
	rigidBody->SetLinearVelocity(b2Vec2(vx * IonixEngine::physicsScale, vy * IonixEngine::physicsScale));
}
