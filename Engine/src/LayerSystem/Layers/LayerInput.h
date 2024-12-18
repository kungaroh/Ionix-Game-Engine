#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"

namespace IonixEngine
{
	class LayerInput : public Layer
	{
	public:
		LayerInput(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(IonixEvent& e) override;
		Input* m_Input;

	private:
		bool OnKeyPressedEvent(Event_KeyPressed& e);
		bool OnMouseButtonPressedEvent(Event_MouseButtonPressed& e);
	};
}