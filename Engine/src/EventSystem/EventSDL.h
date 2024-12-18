#pragma once
#include "EventSystem/Events/EventDefinitions.h"
#include "Window/Window.h"
#include "SDL.h"

namespace IonixEngine
{
    class EventSDL
    {
    public:
        EventSDL() { }
        ~EventSDL() { }

        void PollEventsSDL(SDL_Event e, Window::WindowData& windowData);
    };
}

