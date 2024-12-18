#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerScripting.h"
#include "LayerSystem/Layers/LayerEditor.h"
#include "Scripting/Scripting.h"
#include "Components/ScriptComponent.h"

namespace IonixEngine
{
	void LayerScripting::OnAttach() {
		m_scripting = new Scripting();
		m_scripting->GetVarString("version");
	}

	void LayerScripting::OnDetach() { }

	void LayerScripting::OnLoaded()
	{
		m_scripting->MapImport();
	}

	void LayerScripting::OnUpdate(float deltaTime) { 
		m_scripting->ExecuteLuaCode("UpdateCoroutines("+to_string(deltaTime)+")");
	}

	void LayerScripting::OnFixedUpdate() { }

	void LayerScripting::OnStart() { 
	}

	void LayerScripting::OnEvent(IonixEvent& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Event_WindowClosed>(std::bind(&LayerScripting::OnWindowClosedEvent, this, std::placeholders::_1));
		//dispatcher.Dispatch<Event_OnStart>(std::bind(&LayerScripting::OnStartEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<Event_OnTriggerEnter>(std::bind(&LayerScripting::OnTriggerEnterEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<Event_OnTriggerExit>(std::bind(&LayerScripting::OnTriggerExitEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<Event_OnCollisionEnter>(std::bind(&LayerScripting::OnCollisionEnterEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<Event_OnCollisionExit>(std::bind(&LayerScripting::OnCollisionExitEvent, this, std::placeholders::_1));

	}

	Scripting* LayerScripting::GetScripting() {
		return m_scripting;
	}

	bool LayerScripting::OnWindowClosedEvent(Event_WindowClosed& e)
	{
		Console::info("IonixEvent: Window close");
		Application::Get().m_Running = false;
		return true;
	}

	bool LayerScripting::OnTriggerEnterEvent(Event_OnTriggerEnter& e)
	{
		vector<uint32_t> uids{ (uint32_t)e.GetObj1Id(), (uint32_t)e.GetObj2Id() };
		for (uint32_t i = 0; i < 2; i++)
		{
			Object *o = Application::Get().layerObject->GetScene()->GetObjectByUID(uids[i]);
			ScriptComponent* sc = o->GetComponentOfType<ScriptComponent>();
			if (sc != nullptr)
			{
				sc->OnTriggerEnter(uids[i ^ 1]);
			}
		}
		return true;
	}

	bool LayerScripting::OnCollisionEnterEvent(Event_OnCollisionEnter& e)
	{
		vector<uint32_t> uids{ (uint32_t)e.GetObj1Id(), (uint32_t)e.GetObj2Id() };
		for (uint32_t i = 0; i < 2; i++)
		{
			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uids[i]);
			if (o != nullptr)
			{
				ScriptComponent* sc = o->GetComponentOfType<ScriptComponent>();
				if (sc != nullptr)
				{
					sc->OnCollisionEnter(uids[i ^ 1]);
				}
			}
		}
		return true;
	}

	bool LayerScripting::OnTriggerExitEvent(Event_OnTriggerExit& e)
	{
		vector<uint32_t> uids{ (uint32_t)e.GetObj1Id(), (uint32_t)e.GetObj2Id() };
		for (uint32_t i = 0; i < 2; i++)
		{
			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uids[i]);
			if (o != nullptr)
			{
				ScriptComponent* sc = o->GetComponentOfType<ScriptComponent>();
				if (sc != nullptr)
				{
					sc->OnTriggerExit(uids[i ^ 1]);
				}
			}
		}
		return true;
	}

	bool LayerScripting::OnCollisionExitEvent(Event_OnCollisionExit& e)
	{
		vector<uint32_t> uids{ (uint32_t)e.GetObj1Id(), (uint32_t)e.GetObj2Id() };
		for (uint32_t i = 0; i < 2; i++)
		{
			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uids[i]);
			if (o != nullptr)
			{
				ScriptComponent* sc = o->GetComponentOfType<ScriptComponent>();
				if (sc != nullptr)
				{
					sc->OnCollisionExit(uids[i ^ 1]);
				}
			}
		}
		return true;
	}
}

