#pragma once

#include "Component.h"
#include <b2_world.h>
#include <b2_body.h>
#include <b2_polygon_shape.h>
#include <b2_fixture.h>
#include <b2_circle_shape.h>
#include <b2_contact.h>
#include <b2_contact_manager.h>
#include <b2_settings.h>
#include <sstream>


enum ColliderType
{
	BOX, CIRCLE, POLYGON
};

struct colliderUserData
{
	int collID;
	ColliderType collType;
	b2Fixture* relatedFixture;
};

struct bodyUserData 
{
	int bodyID;
};

class PhysicsComponent : public Component
{
	std::vector<std::shared_ptr<colliderUserData>> mColliderUserData;
	b2World* m_pWorld;
	b2BodyDef rigidBodyDef;
	b2Body* rigidBody;
	int numColliders = 0;
	bodyUserData userData;
	// data needed to create a physics component
	float w, h, restitution, friction, density, pi = 3.1415926f;
	bool isStatic, isTrigger, isKinematic, lockRotation;

public:
	PhysicsComponent(float w, float h, float restitution, float friction, float density, bool isStatic, bool isTrigger, bool isKinematic, bool lockRotation) : Component("Physics"), w(w), h(h), restitution(restitution), friction(friction), density(density), isStatic(isStatic), isTrigger(isTrigger), isKinematic(isKinematic), lockRotation(lockRotation) {}
	~PhysicsComponent();

	virtual void OnStart();

	virtual void OnUpdate(float deltaTime);

	virtual void OnRender() {}

	void SetType(bool isStatic);

	void SetGravityScale(float gravScale);

	void AddForce(float forceX, float forceY, float forcePosX, float forcePosY );

	void AddPolygonCollider() {}

	//if it is possible it might be better to change all the x and y's to vec2s for positions
	void AddBoxCollider(float posX, float posY, float w, float h, bool isTrigger);

	void AddCircleCollider(float posX, float posY, float radius, bool isTrigger);

	void RemoveCollider(int ID);

	void SetDensity(float density);

	void SetRestitution(float restition);

	void SetFriction(float friction);

	void SetRotationActive(bool active);

	void SetTransform(float x, float y);

	void SetRotation(float degree);

	void GetVelocity(float& vx, float& vy);

	void SetVelocity(float vx, float vy);
};


