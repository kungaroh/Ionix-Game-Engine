#include "UIManager.h"

#ifndef IMGUI_DISABLE_DEBUG_TOOLS
#define IMGUI_DEBUG_LOG(...)        ImGui::DebugLog(__VA_ARGS__)
#else
#define IMGUI_DEBUG_LOG(...)        ((void)0)
#endif

namespace IonixEngine
{
    void UIManager::UIInit(SDL_Renderer* renderer, SDL_Window* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();
        
        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
        ImGui_ImplSDLRenderer2_Init(renderer);

        uiQueue = new UIQueue();
        uiGroup = new UIGroup();
    }

    void UIManager::UIUpdate(SDL_Renderer* renderer, SDL_Window* window) //called every frame
    {
        // set flags so there is no debug window drawn
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove;

        // Our state
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        // Reset button states (unpressed at the start of each frame)
        uiQueue->ResetStates();

        // !>> START OF UI LOOP - CREATE FRAME <<!

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame(); 

        //set window size imgui
        //set window pos imgui imvec2
        int width, height;
        SDL_GetWindowSize(window, &width, &height);

        ImGui::SetNextWindowSize(ImVec2(width, height));
        ImGui::SetNextWindowPos(ImVec2(0, 0));

        // !>> UI LOOP DRAW  <<!
        ImGui::Begin("null", nullptr, window_flags); //start of draw

        uiQueue->IterateList();

        ImGui::End(); 

        // !>> END OF DRAW <<!
        // Rendering

        // !>> UI LOOP RENDER <<!
        ImGui::Render();

        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        // HL 13/11/24 - let the RenderClear and RenderPresent happen outside of this - they need to be shared with the main scene renderer
        //SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255), (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
        
        // !>> UI LOOP CLEAR - READY FOR NEXT LOOP <<!
        //SDL_RenderClear(renderer);  // see above - render clear here will remove all the sprites from the scene
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), renderer);
    }
}


//static float f = 0.0f;
//static int counter = 0;
//
//ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//
//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
//
//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
//counter++;
//ImGui::SameLine();
//ImGui::Text("counter = %d", counter);
//
//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//ImGui::End();
