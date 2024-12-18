#include "Window/Window.h"
#include "Architecture/Macros.h"
#include "Logging/Console.h"
#include "EventSystem/Event.h"
#include "EventSystem/Events/EventDefinitions.h"
#include "Architecture/Application.h"
#include <iostream>
#include "EventSystem/EventSDL.h"
#include <SDL_mixer.h>

namespace IonixEngine
{
    Window* Window::Create(const WindowProps& props)
    {
        return new Window(props);
    }

    Window::Window(const WindowProps& props)
    {
        Init(props);
    }

    Window::~Window()
    {
        ShutDown();
    }

    void Window::Init(const WindowProps& props)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
            return;
        }

        // Iniialize SDL Mixer - Centralise SDL iniialisation
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
            SDL_Log("Unable to initialize SDL_mixer: %s", Mix_GetError());
            return;
        }

        // Create SDL window
        m_Window = SDL_CreateWindow(
            props.Title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            static_cast<int>(props.Width),
            static_cast<int>(props.Height),
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );
        if (!m_Window) {
            std::cerr << "Failed to create SDL window: " << SDL_GetError() << std::endl;
            return;
        }

        // Create SDL renderer
        m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (!m_Renderer) {
            std::cerr << "Failed to create SDL renderer: " << SDL_GetError() << std::endl;
            SDL_DestroyWindow(m_Window);
            return;
        }

        // Store custom data in the window
        m_Data.Title = props.Title;
        m_Data.Width = props.Width;
        m_Data.Height = props.Height;
        SDL_SetWindowData(m_Window, "customData", &m_Data);
        m_Input = new Input();

    }

    void Window::ShutDown()
    {
        SDL_DestroyRenderer(m_Renderer);
        SDL_DestroyWindow(m_Window);
        SDL_Quit();
    }

    void Window::OnUpdate()
    {
       
    }
}