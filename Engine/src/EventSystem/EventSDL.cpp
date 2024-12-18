#include "EventSystem/EventSDL.h"
#include "imgui.h"
#include <backends/imgui_impl_sdl2.h>

namespace IonixEngine
{
    void EventSDL::PollEventsSDL(SDL_Event e, Window::WindowData& windowData)
    {
        switch (e.type)
        {
            case SDL_WINDOWEVENT:
                switch (e.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:
                {
                    Event_WindowClosed event;
                    windowData.EventCallback(event);
                    break;
                }
                default:
                    break;
                }
                break;

            default:
                break;

            case SDL_KEYDOWN:
            {
                int keycode = e.key.keysym.sym;
                Event_KeyPressed event(keycode);
                windowData.EventCallback(event);
                break;
            }
        }
    }
}
