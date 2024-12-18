#include "Application.h"
#include "Logging/Console.h"
#include "Architecture/EngineSystems.h"
#include "Scripting/EngineHooks/EngineHooks.h"
#include "../ResourceManager.h"
#include "Components/ScriptComponent.h"
#include "Components/SpriteComponent.h"

#define JM_TEST

namespace IonixEngine {
    Application* Application::s_Instance = nullptr;
}

namespace IonixEngine
{

#ifdef JM_TEST
    extern void InitJMTest();
#endif


    #define BIND_EVENT_FN(fn) std::bind(&Application::fn, this, std::placeholders::_1)
    Application& Application::Get() { return *s_Instance; }

    Application::Application()
    {
        s_Instance = this;

        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));


#ifdef JM_TEST
        EngineSystems::InitSystems("../TestProjectData");
#endif


        //LAYER IDS
        const int LAYER_EDITOR_ID = 0;
        const int LAYER_INPUT_ID = 1;
        const int LAYER_GRAPHICS_ID = 2;
        const int LAYER_PHYSICS_ID = 3;
        const int LAYER_SCRIPTING_ID = 4;
        const int LAYER_AUDIO_ID = 5;
        const int LAYER_OBJECT_ID = 6;
        const int LAYER_UI_ID = 7;
        
        //EDITOR LAYER
        AddLayer(new LayerEditor(LAYER_EDITOR_ID));
        layerEditor = dynamic_cast<LayerEditor*>(m_LayerStack.GetLayerByID(LAYER_EDITOR_ID));
      
        //INPUT LAYER
        AddLayer(new LayerInput(LAYER_INPUT_ID));
        layerInput = dynamic_cast<LayerInput*>(m_LayerStack.GetLayerByID(LAYER_INPUT_ID));
      
        //GRAPHICS LAYER
        AddLayer(new LayerGraphics(LAYER_GRAPHICS_ID));
        layerGraphics = dynamic_cast<LayerGraphics*>(m_LayerStack.GetLayerByID(LAYER_GRAPHICS_ID));

        //PHYSICS LAYER
        AddLayer(new LayerPhysics(LAYER_PHYSICS_ID));
        layerPhysics = dynamic_cast<LayerPhysics*>(m_LayerStack.GetLayerByID(LAYER_PHYSICS_ID));
      
        //SCRIPTING LAYER
        AddLayer(new LayerScripting(LAYER_SCRIPTING_ID));
        layerScripting = dynamic_cast<LayerScripting*>(m_LayerStack.GetLayerByID(LAYER_SCRIPTING_ID));

        //AUDIO LAYER
        AddLayer(new LayerAudio(LAYER_AUDIO_ID));
        layerAudio = dynamic_cast<LayerAudio*>(m_LayerStack.GetLayerByID(LAYER_AUDIO_ID));

        //OBJECT LAYER
        AddLayer(new LayerObject(LAYER_OBJECT_ID));
        layerObject = dynamic_cast<LayerObject*>(m_LayerStack.GetLayerByID(LAYER_OBJECT_ID));

        //UI LAYER
        AddLayer(new LayerUI(LAYER_UI_ID));
        layerUI = dynamic_cast<LayerUI*>(m_LayerStack.GetLayerByID(LAYER_UI_ID));

        std::string path = ResourceManager::GetInstance().TEXTURE_PATH + "Background.png";
        std::vector<SDL_Surface*> testStructure = ResourceManager::GetInstance().RipToPieces(path);
    
    
        for (auto layer : m_LayerStack.GetLayers())
        {
            layer->OnLoaded();
        }
    }

    Application::~Application()
    {

    }

    void Application::OnEvent(IonixEvent& e)
    {
        for (auto layer : m_LayerStack.GetLayers()) {
            layer->OnEvent(e);
            if (e.m_Handled)
                break;
        }
    }

    void Application::Run()
    {

        m_Running = true;

        double dt = 1 / 60.0;
        double currentTime = double(SDL_GetPerformanceCounter()) / SDL_GetPerformanceFrequency();

        double accumulator = 0.0;
        
#ifdef JM_TEST
    //InitJMTest();
#endif


        while (m_Running)
        {
            double newTime = double(SDL_GetPerformanceCounter()) / SDL_GetPerformanceFrequency();
            double frameTime = newTime - currentTime;
            currentTime = newTime;

            accumulator += frameTime;
            while (accumulator >= dt)
            {
                float deltaTime = min(frameTime, dt);
                //integrate(state, t, deltaTime);
                layerEditor->OnUpdate();
                layerInput->OnUpdate();
                layerScripting->OnUpdate(dt);
                layerUI->OnUpdate();
                layerPhysics->OnUpdate(dt);
                layerObject->OnUpdate(dt);
                layerGraphics->OnUpdate(dt);
                layerAudio->OnUpdate(dt);
                //std::cout << "Loop ran" << std::endl;
                accumulator -= dt;
            }
            // clean up objects marked for deletion during update
            layerObject->ClearDeletedObjects();

            // render - scene, then UI
            layerGraphics->StartRender();
            layerGraphics->StartZSort();
            layerObject->OnRender();
            layerGraphics->FinishZSort();
            //std::cout << "finished render" << std::endl;
            layerGraphics->FinishRender();
            m_Window->OnUpdate();
        }
    }
}
