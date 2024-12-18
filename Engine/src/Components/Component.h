#pragma once

#include <string>
#include <cinttypes>

#include "../Objects/ObjectUID.h"
#include "../Objects/Object.h"

using namespace std;

// ------------------ PSA COMPONENT NAMES SHOULD BE "NameComponent" | PSA COMPONENT NAMES SHOULD BE "NameComponent"  ------------------ \\
// ------------------ EXAMPLE: "ScriptComponent", "TransformComponent", "PhysicsComponent" IF INCORRECT SOME FUNCTIONS WILL NOT WORK ------------------ \\

class Component
{
	// abstract base class
	string type;
	uint32_t uid;
protected:
	Object* m_owner = nullptr;
public:
	Component(string type) : type(type), uid(ObjectUID::UID()) {}
	virtual ~Component() {}
	void SetOwner(Object* owner) { m_owner = owner; }
	Object* GetOwner() const { return m_owner; }
	string GetType() const { return type; }
	uint32_t GetUID() const { return uid;  }

	virtual void OnStart() = 0;
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;
	
};
