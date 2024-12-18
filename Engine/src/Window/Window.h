#pragma once
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>
#include "Architecture/Macros.h"
#include "EventSystem/Event.h"
#include <Input/Input.h>

namespace IonixEngine
{
    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        WindowProps(const std::string& title = "Ionix Engine",
            unsigned int width = 960,
            unsigned int height = 640)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    class ENGINE_API Window
    {
    public:
        using EventCallbackFn = std::function<void(IonixEvent&)>;

        Window(const WindowProps& props);
        virtual ~Window();

        void OnUpdate();

        inline unsigned int GetWidth() const { return m_Data.Width; }
        inline unsigned int GetHeight() const { return m_Data.Height; }
        inline SDL_Window* GetSdlWindow() const { return m_Window; }
        inline SDL_Renderer* GetSdlRenderer() const { return m_Renderer; }

        inline void SetEventCallback(const EventCallbackFn& callback) { m_Data.EventCallback = callback; }

        static Window* Create(const WindowProps& props = WindowProps());

        virtual void Init(const WindowProps& props);
        virtual void ShutDown();

        SDL_Window* m_Window;
        SDL_Renderer* m_Renderer;
        Input* m_Input;

        struct WindowData
        {
            std::string Title;
            unsigned int Width, Height;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
    };
}