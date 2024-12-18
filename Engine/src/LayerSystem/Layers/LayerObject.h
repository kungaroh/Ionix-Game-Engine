#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"
#include "Objects/Scene.h"
#include "Objects/Object.h"

namespace IonixEngine
{
	class EditorInterpreter;

	class LayerObject : public Layer
	{
	public:
		LayerObject(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		void OnUpdate(float deltaTime);
		virtual void OnEvent(IonixEvent& e) override;
		void OnRender();
		void SetCurScene(Scene curScene);

		void CreateTilemapLayerObject(TiledData tiledData, EditorInterpreter& ei);
		void CreateTiledObjects(TiledData tiledData, EditorInterpreter& ei);
		void AddScriptsToObjects(TiledData data);
		void ClearDeletedObjects()
		{
			m_objects->ClearDeleteList();
		}
		Object* NewObject(const char* name);
		Object* GetObject(uint32_t i);
		Object* GetObject(const char* i);
		Scene* GetScene();

		std::unordered_map<int, Object*> tileObjectMap;
		vector<Object*> tileObjectArray;
	private:
		Scene* m_objects;

		bool OnWindowClosedEvent(Event_WindowClosed& e);
		bool OnTileMapDataLoaded(Event_OnTileMapDataLoaded& e);
	};
}