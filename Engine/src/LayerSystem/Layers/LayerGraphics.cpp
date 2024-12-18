#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerGraphics.h"
#include "LayerSystem/Layers/LayerGraphics.h"

namespace IonixEngine
{
	void LayerGraphics::OnAttach() 
	{ 
		SDL_Renderer* renderer = Application::Get().GetWindow().m_Renderer;
		m_graphics = new Graphics(renderer);
	}

	void LayerGraphics::OnDetach() { }

	void LayerGraphics::OnLoaded()
	{
	}

	void LayerGraphics::OnUpdate(float deltaTime) { 
		// HL - this shouldn't be rendering anything, this is already happening in layerObject->OnRender()
		//StartRender();
		//TestGraphics();
		//FinishRender();
	}

    void LayerGraphics::OnEvent(IonixEvent& e)
    {
		EventDispatcher dispatcher(e);
		
		dispatcher.Dispatch<Event_WindowClosed>(std::bind(&LayerGraphics::OnWindowClosedEvent, this, std::placeholders::_1));
    }

	bool LayerGraphics::OnWindowClosedEvent(Event_WindowClosed& e)
	{
		Console::info("IonixEvent: Window close");
		Application::Get().m_Running = false;
		return true;
	}


	//FUNCTIONS SPECIALISED TO THIS LAYER

	void LayerGraphics::StartRender() { 
		m_graphics->StartRender();
	}

	void LayerGraphics::FinishRender() {
		m_graphics->FinishRender();
	}

	void LayerGraphics::StartZSort()
	{
		m_graphics->StartZSort();
	}
	void LayerGraphics::FinishZSort()
	{
		m_graphics->FinishZSort();
	}

	
	//void LayerGraphics::AddEntityToSystem(SpriteComponent* sprite)
	//{
		//m_graphics->AddEntityToSystem(sprite);
	//}

	
	void LayerGraphics::DrawSprite(Sprite& sprite) {
		m_graphics->DrawSprite(sprite);

	}

	TextureManager* LayerGraphics::GetTextureManager() {
		return m_graphics->GetTextureManager();
	}

	SDL_Renderer* LayerGraphics::GetRenderer() {
		return m_graphics->GetRenderer();
	}
	void LayerGraphics::SetRenderer(SDL_Renderer* renderer) {
		m_graphics->SetRenderer(renderer);
	}
	void LayerGraphics::TestGraphics() {
		m_graphics->TestGraphics();
	}

}

