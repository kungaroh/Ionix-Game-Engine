#pragma once

#include <string>
#include <cinttypes>
#include "Component.h"
#include <vector>

using namespace std;

// basic transform component
// it includes hierarchy structure, but propagating transforms from parent to child is to do.
class TransformComponent : public Component
{
	TransformComponent* parent = nullptr;
	vector<TransformComponent*> children;
public:
	// Making these public because getters and setters wouldn't do anything other than get and set the values
	float x, y; // position
	float sx = 1.0f; 
	float sy = 1.0f; // scale
	float angle = 0.0f; // rotation
	int z = 0; // z layer - smaller is closer to the camera

	TransformComponent() : Component("Transform") 
	{
	}
	virtual ~TransformComponent() {}

	virtual void OnStart() override
	{
	}
	virtual void OnUpdate(float deltaTime) override
	{
	}
	virtual void OnRender() override
	{
	}
	// methods specific to TransformComponent
	void SetParent(TransformComponent* p) { parent = p; }
	void AddChild(TransformComponent* c) { children.push_back(c); }
	TransformComponent* GetChild(uint32_t i) const { return children[i]; }
	uint32_t GetNumChildren() const { return children.size(); }
};