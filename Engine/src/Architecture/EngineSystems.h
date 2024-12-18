#pragma once
#include "../graphics/graphics.h"
#include "../Scripting/scripting.h"
#include "../Objects/Scene.h"
#include "../Physics/Physics.h"

#include <string>

namespace IonixEngine
{
	class EngineSystems
	{
		static std::string m_projectPath;

	public:
		static void InitSystems(std::string projectPath );  
		static std::string ProjectPath() { return m_projectPath; }		
	};
}