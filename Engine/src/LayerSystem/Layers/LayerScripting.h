#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"
#include "Components/ScriptComponent.h"

namespace IonixEngine
{
	class LayerScripting : public Layer
	{
	public:
		LayerScripting(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		void OnUpdate(float deltaTime);
		virtual void OnFixedUpdate();
		virtual void OnEvent(IonixEvent& e) override;
		virtual void OnStart();
		Scripting* GetScripting();

		ScriptComponent* script3;	

	private:
		Scripting* m_scripting;
		bool OnWindowClosedEvent(Event_WindowClosed& e);
		bool OnKeyPressedEvent(Event_KeyPressed& e);
		bool OnTriggerEnterEvent(Event_OnTriggerEnter& e);
		bool OnCollisionEnterEvent(Event_OnCollisionEnter& e);
		bool OnTriggerExitEvent(Event_OnTriggerExit& e);
		bool OnCollisionExitEvent(Event_OnCollisionExit& e);

	};
}