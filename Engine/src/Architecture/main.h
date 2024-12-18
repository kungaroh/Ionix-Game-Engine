#pragma once
using namespace IonixEngine;

#include "Architecture/Application.h"
#include "Logging/Console.h"

namespace ClientApp
{
    IonixEngine::Application* CreateApplication();
}

int main(int argc, char** argv)
{
    Application* app = ClientApp::CreateApplication();
    app->Run();

    delete app;
    return 0;
}
