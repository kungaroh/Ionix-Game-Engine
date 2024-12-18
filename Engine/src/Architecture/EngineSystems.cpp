#include "EngineSystems.h"
#include <Logging/Console.h>
using namespace IonixEngine;

std::string EngineSystems::m_projectPath;

namespace IonixEngine
{ 
	void EngineSystems::InitSystems(std::string projectPath)
	{
		Console::initialize(LogLevel::INFO);
		Console::info("Console initialized.");

		m_projectPath = projectPath;
	}
}