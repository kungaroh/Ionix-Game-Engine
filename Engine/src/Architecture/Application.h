#pragma once
#include "Window/Window.h"
#include "Macros.h"
#include "EventSystem/Event.h"
#include "EventSystem/Events/EventDefinitions.h"
#include "LayerSystem/LayerStack.h"
#include "Physics/Physics.h"
#include "Objects/Scene.h"
#include "LayerSystem/Layers/LayerEditor.h"
#include "LayerSystem/Layers/LayerInput.h"
#include "LayerSystem/Layers/LayerGraphics.h"
#include "LayerSystem/Layers/LayerPhysics.h"
#include "LayerSystem/Layers/LayerScripting.h"
#include "LayerSystem/Layers/LayerAudio.h"
#include "LayerSystem/Layers/LayerObject.h"
#include "LayerSystem/Layers/LayerUI.h"
#include <Objects/TestObject.h>
#include "Audio/Audio.h"
//#define TESTING_PHYSICS
#ifdef TESTING_PHYSICS
class PhysicsComponent;
#endif

//#define SCRIPTING_TEST
//#define AUDIO_TEST
#ifdef SCRIPTING_TEST
#include "Components/ScriptComponent.h"
#endif // SCRIPTING_TEST

#ifdef Test_Graphics
//#include "Components/SpriteComponent.h"
class SpriteComponent;
#endif // Test_Graphics


namespace IonixEngine
{    
    //class Graphics; redundant?

    class ENGINE_API Application
    {
    public:
        static Application& Get();

        Application();
        virtual ~Application();

        bool m_Running = true;

        inline Window& GetWindow() { return *m_Window; }

        void Run();
        void OnEvent(IonixEvent& e);
        
        inline void AddLayer(Layer* layer) 
        {   
            m_LayerStack.PushLayer(layer); 
            layer->OnAttach(); 
        }

        LayerEditor* layerEditor;
        LayerInput* layerInput;
        LayerGraphics* layerGraphics;
        LayerPhysics* layerPhysics;
        LayerScripting* layerScripting;
        LayerAudio* layerAudio;
        LayerObject* layerObject;
        LayerUI* layerUI;


        //Graphics* GetGraphics() { return m_graphics; } //redundant
  
#ifdef TESTING_PHYSICS 
        Physics* GetPhysics() { return m_physics; }
        PhysicsComponent* physComp1;
        PhysicsComponent* physComp2;
        PhysicsComponent* groundPhysComp;
#endif 
       // Scripting* GetScripting() { return m_scripting; } //redundant
        // Scene* GetScene() { return m_objects; }

    private:
        static Application* s_Instance;
        UIManager* m_UIManager;

        //Graphics* m_graphics; //redundant
        //Physics* m_physics;//redundant
        //Scripting* m_scripting; //redundant
        //Physics* m_physics; //redundant
        //Scene* m_objects;
#ifdef SCRIPTING_TEST
        Scripting* m_scripting;
        

        ScriptComponent* script1;
        ScriptComponent* script2;
        ScriptComponent* script3;
#endif // SCRIPTING_TEST

#ifdef AUDIO_TEST
        Audio* audio;
#endif
#ifdef Test_Graphics
        Graphics* m_graphics;
        SpriteComponent* Render1;
        SpriteComponent* Render2;
        SpriteComponent* Render3;
#endif // Test_Graphics

        
        
        //TestObject* testObject;

        std::unique_ptr<Window> m_Window;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}