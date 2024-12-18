#pragma once
#include <vector>
#include <cinttypes>
#include <string>
#include "ObjectUID.h"


using namespace std;
class Component;

class Object
{
	uint32_t uid;
	string gameObjectName;
	bool isEnabled = true;
	string tag = "DefaultTag";
	vector<Component*> componentList;
	void AddTransform();
	void CopyComponentsFrom(const Object* other);
	void GetObjectPosition(const Object* obj, float& outX, float& outY) const;

public:
	Object() : uid(ObjectUID::UID()) { AddTransform(); }
	~Object();

	void SetUid(uint32_t id) { uid = id; }

	void SetGameObjectName(const char* n) { gameObjectName = n; }
	string GetGameObjectName() { return gameObjectName; }

	// API - all implemented

	void AddComponent(Component* comp);
	void RemoveComponent(Component* comp);
	void RemoveComponent(uint32_t index);
	void StartAllComponents();
	void UpdateAllComponents(float deltaTime);
	void RenderAllComponents();
	void SetObjectPosition(float x, float y);
	void SetObjectZLayer(int z);
	int GetObjectZLayer();
	bool IsEnabled() { return isEnabled; }
	void DisableObject();
	void EnableObject();
	void SetTag(string newTag) { tag = newTag; }
	string GetTag() const { return tag; }

	// Cloning
	Object* Clone() const;
	static Object* Instantiate(const Object* original);
	static Object* Instantiate(const Object* original, float x, float y);
	static uint32_t Instantiate1(const Object* original, float x, float y, int t = 0);

	uint32_t GetNumComponents() const;
	Component* GetComponent(uint32_t index) const;
	
	template<class T> T* GetComponentOfType() const
	{
		for (auto* i : componentList)
		{
			// This ensures that i (the current component) is not null
			if (!i)
			{
				std::cerr << "Invalid component!" << std::endl;
				continue;
			}
#if 0 // HL 13/11/24 - code below doesn't work - easier alternative in the else branch
			// Gets the name of the type e.g. "class IonixEngine::ScriptComponent"
			std::string s = typeid(T).name();
			// Gets the current component type
			std::string type = i->GetType();
			// Gets the position of "::" in the string (+2 so the position is *after* the "::"
			int pos = s.find("::") +2;
			// Get the position of "Component" in the string (This get the start of component/the end of component name)
			int pos2 = s.find("Component");

			// substrings gets the number of characters between pos and pos2 and sets it to the string e.g. Script
			string substring = s.substr(pos, (pos2 - pos));
			
			// Returns the component if it's type matches the type passed in
			if (type == substring)
			{
				return dynamic_cast<T*>(i);
			}
#else
			if (dynamic_cast<T*>(i) != nullptr)
				return dynamic_cast<T*>(i);
#endif
		}
		// In case for loop ends without finding component of type specified
		return nullptr;
	}

	uint32_t UID() const { return uid; }
};