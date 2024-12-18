#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"
#include "graphics/Graphics.h"
namespace IonixEngine
{

	class LayerGraphics : public Layer
	{
	public:
		LayerGraphics(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		void OnUpdate(float deltaTime);
		virtual void OnEvent(IonixEvent& e) override;
		//FUNCTIONS SPECIALISED TO THIS LAYER
		void StartRender();
		void FinishRender();
		void StartZSort();
		void FinishZSort();
		void DrawSprite(Sprite& sprite);
		TextureManager* GetTextureManager();
		void AddEntityToSystem(SpriteComponent* sprite);

		SDL_Renderer* GetRenderer();
		void SetRenderer(SDL_Renderer* renderer);
		void TestGraphics();

		Graphics* GetGraphics() { return m_graphics; }
	private:
		Graphics* m_graphics;
		bool OnWindowClosedEvent(Event_WindowClosed& e);
		bool OnKeyPressedEvent(Event_KeyPressed& e);
	};
}