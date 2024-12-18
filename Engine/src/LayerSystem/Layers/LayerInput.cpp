#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerInput.h"
#include "LayerSystem/Layers/LayerInput.h"
#include <EventSystem/EventSDL.h>
#include <Scripting/EngineHooks/EngineHooksInput.h>

namespace IonixEngine
{
	void LayerInput::OnAttach() 
	{ 
		m_Input = new Input();
		InitKeyBinds();
		InitMouseBinds();
	}

	void LayerInput::OnDetach() { }

	void LayerInput::OnLoaded()
	{
	}

	void LayerInput::OnUpdate() 
	{
		SDL_Event e;
		EventSDL eventSDL;

		m_Input->ClearInputs();

		while (SDL_PollEvent(&e))
		{
			ImGui_ImplSDL2_ProcessEvent(&e);
			Window::WindowData& data = *(Window::WindowData*)SDL_GetWindowData(Application::Get().GetWindow().m_Window, "customData");
			eventSDL.PollEventsSDL(e, data);
			m_Input->OnUpdate(e);
			//std::cout << "poll" << endl;
		}
		/*if (m_Input->IsKeyDown(Keycode::Ionix_Space))
		{
			std::cout << "key is pressed" << endl;
		}
		if (m_Input->IsKeyUp(Keycode::Ionix_Space))
		{
			std::cout << "key is up" << endl;
		}
		if (m_Input->IsKeyHeld(Keycode::Ionix_Space))
		{
			std::cout << "key is held" << endl;
		}*/
		/*if (m_Input->IsMouseDown(Mousecode::Ionix_Mouse2))
		{
			std::cout << "mouse is pressed" << endl;
		}
		if (m_Input->IsMouseUp(Mousecode::Ionix_Mouse2))
		{
			std::cout << "mouse is up" << endl;
		}
		if (m_Input->IsMouseHeld(Mousecode::Ionix_Mouse2))
		{
			std::cout << "mouse is held" << endl;
		}
		std::cout << "mouse X position: " << m_Input->GetMouseX() << endl;
		std::cout << "mouse Y position: " << m_Input->GetMouseY() << endl;*/
	}

	void LayerInput::OnEvent(IonixEvent& e)
	{
		EventDispatcher dispatcher(e);

		// Dispatch for key press event
		dispatcher.Dispatch<Event_KeyPressed>(std::bind(&LayerInput::OnKeyPressedEvent, this, std::placeholders::_1));

		// Dispatch for mouse button press event
		dispatcher.Dispatch<Event_MouseButtonPressed>(std::bind(&LayerInput::OnMouseButtonPressedEvent, this, std::placeholders::_1));
	}

	bool LayerInput::OnKeyPressedEvent(Event_KeyPressed& e)
	{
		return true;
	}

	bool LayerInput::OnMouseButtonPressedEvent(Event_MouseButtonPressed& e)
	{
		return false;
	}

}
