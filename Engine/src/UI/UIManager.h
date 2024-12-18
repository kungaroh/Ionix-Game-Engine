#pragma once
#include <SDL.h>
#include <imgui.h>
#include <third-party/ImGuiRenderer.h>
#include <third-party/imgui_impl_sdlrenderer2.h>
#include <io.h>
#include "UIGroup.h"
#include "UI/UIQueue.h"

namespace IonixEngine
{
	class UIManager
	{
	public:
		UIManager()
		{
		}
		~UIManager() {};
		void UIInit(SDL_Renderer* renderer, SDL_Window* window);
		void UIUpdate(SDL_Renderer* renderer, SDL_Window* window);
		UIQueue* uiQueue;
		UIGroup* uiGroup;
	};
}


