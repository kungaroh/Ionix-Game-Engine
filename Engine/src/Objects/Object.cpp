#include "Object.h"
#include "../Components/Component.h"
#include <vector>
#include <Components/ComponentFactory.h>

Object::~Object()
{ // All components should be deleted/destroyed here
	auto it = componentList.begin();

	while (it != componentList.end())
	{
		delete* it;
		it = componentList.erase(it);
	}
}

void Object::AddComponent(Component* comp)
{
	componentList.push_back(comp);
	comp->SetOwner(this);
	//comp->OnStart(); // this is already happening when adding object to scene, which is the right place(HL 13/11/24)
}

void Object::RemoveComponent(Component* comp)
{
	auto it = componentList.begin();
	
	while (it != componentList.end())
	{
		if (comp == *it)
		{
			delete *it;
			it = componentList.erase(it);
			break;
		}
		else
		{
			it++;
		}
	}

}

void Object::RemoveComponent(uint32_t index)
{
	auto it = componentList.begin();
	Component* comp = Object::GetComponent(index);

	while (it != componentList.end())
	{
		if (comp == *it)
		{
			delete* it;
			it = componentList.erase(it);
			break;
		}
		else
		{
			it++;
		}
	}
}

Component* Object::GetComponent(uint32_t index) const
{
	auto it = componentList.begin();
	std::advance(it, index); // Move iterator to the specified index
	return *it; // Return pointer to the component
}


void Object::StartAllComponents()
{
	for (auto* i : componentList)
	{
		i->OnStart();
	}
}

uint32_t Object::GetNumComponents() const
{
	return componentList.size();
}

void Object::UpdateAllComponents(float deltaTime)
{
	if (componentList.size() == 0)
	{
		return;
	}
	for (auto* i : componentList)
	{
		if (i != nullptr)
		{
			i->OnUpdate(deltaTime);
		}
	}
}

void Object::RenderAllComponents()
{
	for (auto* i : componentList)
	{
		i->OnRender();
	}
}

void Object::SetObjectPosition(float x, float y)
{
    GetComponentOfType<TransformComponent>()->x = x;
    GetComponentOfType<TransformComponent>()->y = y;
}

void Object::SetObjectZLayer(int z)
{
	GetComponentOfType<TransformComponent>()->z = z;
}

int Object::GetObjectZLayer()
{
	return GetComponentOfType<TransformComponent>()->z;
}

void Object::DisableObject()
{
	isEnabled = false;
}

void Object::EnableObject()
{
	isEnabled = true;
}

void Object::AddTransform()
{
	// add the default transform component
	TransformComponent* tc = new TransformComponent();
	componentList.push_back(tc);

}

void Object::GetObjectPosition(const Object* obj, float& outX, float& outY) const {
    outX = 0.0f;
    outY = 0.0f;
    if (obj) {
        if (auto transform = obj->GetComponentOfType<TransformComponent>()) {
            outX = transform->x;
            outY = transform->y;
        }
    }
}

Object* Object::Clone() const {
    Object* newObj = new Object();
    newObj->CopyComponentsFrom(this);
	// copy tag
	newObj->tag = tag;
    return newObj;
}

Object* Object::Instantiate(const Object* original) {
    if (!original) return nullptr;
    return original->Clone();
}

Object* Object::Instantiate(const Object* original, float x, float y) {
    if (!original) return nullptr;

    Object* clone = original->Clone();

    if (TransformComponent* transform = clone->GetComponentOfType<TransformComponent>()) {
        transform->x = x;
        transform->y = y;
    }

    return clone;
}
uint32_t Object::Instantiate1(const Object* original, float x, float y, int t)
{
	if (!original) return 0;

	Object* clone = original->Clone();

	if (TransformComponent* transform = clone->GetComponentOfType<TransformComponent>()) {
		transform->x = x;
		transform->y = y;
	}

	return clone->UID();
}

void Object::CopyComponentsFrom(const Object* other) {
	if (!other) return;

	for (const auto* comp : other->componentList) {
		Component* newComp = ComponentFactory::CopyComponent(comp);
		if (newComp && newComp->GetType() != "Transform") {
			this->AddComponent(newComp);
		}
	}
}
