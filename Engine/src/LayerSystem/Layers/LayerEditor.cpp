#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerEditor.h"
#include "LayerSystem/Layers/LayerEditor.h"

namespace IonixEngine
{
	void LayerEditor::OnAttach() { }

	void LayerEditor::OnDetach() { }

	void LayerEditor::OnLoaded() { }

	void LayerEditor::OnUpdate() { }

    void LayerEditor::OnEvent(IonixEvent& e)
    {
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<Event_WindowClosed>(std::bind(&LayerEditor::OnWindowClosedEvent, this, std::placeholders::_1));
    }

	bool LayerEditor::OnWindowClosedEvent(Event_WindowClosed& e)
	{
		//Console::info("IonixEvent: Window close");
		Application::Get().m_Running = false;
		return true;
	}


}

