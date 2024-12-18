#include "Scene.h"
#include "Architecture/Application.h"
#include <sstream>

Scene* Scene::m_curScene;

Object* Scene::GetObject(uint32_t index) const
{
	auto it = objectList.begin();
	std::advance(it, index); 
	return *it;
}

Object* Scene::GetObjectByUID(uint32_t uid)
{
	if (objectReferences.find(uid) == objectReferences.end())
	{
		return nullptr;
	}
	return objectReferences[uid];	
}

// bind
uint32_t Scene::GetUIDByName(const char* name)
{
	if (stringUID.find(name) == stringUID.end())
	{
		return -1;
	}
	return stringUID.at(name);
}

void Scene::SetObjectName(uint32_t uid, const char* name)
{
	Object* obj = GetObjectByUID(uid);
	if (obj != nullptr)
	{
		if (stringUID.find(GetObjectByUID(uid)->GetGameObjectName()) != stringUID.end())
		{
			auto it = stringUID.find(GetObjectByUID(uid)->GetGameObjectName());
			stringUID.erase(it);
		}
		stringUID[name] = uid;
		obj->SetGameObjectName(name);
	}
}

void Scene::AddObject(Object* obj) // Basically OnStart()
{
	objectReferences[obj->UID()] = obj;
	stringUID[obj->GetGameObjectName()] = obj->UID();
	objectList.push_back(obj);
	obj->StartAllComponents();
}


void Scene::RemoveObject(Object* obj)
{
	auto it = objectList.begin();
	while (it != objectList.end())
	{
		if (obj == *it)
		{
			delete* it;
			it = objectList.erase(it);

			break;
		}
		else
		{
			it++;
		}
	}
	objectReferences.erase(obj->UID());
	stringUID.erase(obj->GetGameObjectName());
}

void Scene::RemoveObject(uint32_t uid)
{
	auto it = objectList.begin();
	Object* obj = Scene::GetObjectByUID(uid);

	while (it != objectList.end())
	{
		if (obj == *it)
		{
			delete* it;
			it = objectList.erase(it);
			break;
		}
		else 
		{
			it++;
		}
	}
	objectReferences.erase(uid);
	stringUID.erase(obj->GetGameObjectName());
}

void Scene::OnUpdate(float deltaTime)// calls the update function for the objects
{
	// use a for loop that queries list size because object updats may spawn new objects! 
	//int n = objectReferences.size();
	for (auto& o : objectReferences)
	{
		if (o.second == nullptr) continue;
		if (o.second->IsEnabled())
		{
			if (o.second->GetNumComponents() > 0)
			{
				o.second->UpdateAllComponents(deltaTime);
			}

		}
	}
}

void Scene::OnRender()
{
	for (auto& o : objectReferences)
	{
		if (o.second == nullptr) continue;

		if (o.second->IsEnabled())
		{
			if (o.second->GetNumComponents() > 0)
			{
				o.second->RenderAllComponents();
			}
		}
	}
}

uint32_t Scene::InstantiateAtPosition(uint32_t originalUID, float x, float y) {
	Object* original = GetObjectByUID(originalUID);
	if (original == nullptr) return 0;

	Object* clone = Object::Instantiate(original, x, y);
	if (clone == nullptr) return 0;
	AddObject(clone);
	return clone->UID();
}

uint32_t Scene::InstantiateAtPosition(const char* gameObjectName, float x, float y) {
	uint32_t original = Scene::GetUIDByName(gameObjectName);

	if (original == -1) return 0;

	Object* o = GetObjectByUID(original);
	Object* clone = Object::Instantiate(o, x, y);
	clone->SetObjectZLayer(o->GetObjectZLayer());

	if (clone == nullptr) return 0;
	
	string name = string(gameObjectName) + to_string(clone->UID());
	clone->SetGameObjectName(name.c_str());
	
	AddObject(clone);
	return clone->UID();
}