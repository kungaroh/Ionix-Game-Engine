#pragma once
#include "Object.h"
#include "../Components/Component.h"
#include <vector>
#include <cinttypes>
#include "unordered_map"
using namespace std;

class Scene
{
public:
	// API - all implemented
	uint32_t GetNumObjects() const { return objectList.size(); }
	Object* GetObject(uint32_t index) const;

	Object* GetObjectByUID(uint32_t uid);
	uint32_t  GetUIDByName(const char*);
	void SetObjectName(uint32_t uid, const char* name);
	void AddObject(Object* obj); // basically On start
	void RemoveObject(Object* obj);
	void RemoveObject(uint32_t index);
	void OnUpdate(float deltaTime); // calls the update function for the objects
	void OnRender();

	vector<Object*> GetObjectList() { return objectList; }

	uint32_t InstantiateAtPosition(uint32_t originalUID, float x, float y);
	uint32_t InstantiateAtPosition(const char* gameObjectName, float x, float y);

	static Scene* m_curScene;
	static Scene* GetCurScene() { return m_curScene; }
	static void SetCurScene(Scene* s) { m_curScene = s; }

	void MarkForDelete(Object* o) { deleteList.push_back(o); }
	void ClearDeleteList()
	{
		for (auto o : deleteList)
		{
			RemoveObject(o);
		}
		deleteList.clear();
	}
private:
	 vector<Object*> objectList;
	 std::unordered_map<uint32_t, Object*> objectReferences;
	 std::unordered_map<string, uint32_t> stringUID;

	 vector<Object*> deleteList;

};