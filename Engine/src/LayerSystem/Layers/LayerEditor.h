#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"

namespace IonixEngine
{
	class LayerEditor : public Layer
	{
	public:
		LayerEditor(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(IonixEvent& e) override;

	private:
		bool OnWindowClosedEvent(Event_WindowClosed& e);
		bool OnKeyPressedEvent(Event_KeyPressed& e);
	};
}