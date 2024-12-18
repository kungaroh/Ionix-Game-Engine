#pragma once
#include "Component.h"
#include "Scripting/Scripting.h"
#include <iostream>
#include <string>
using namespace std;


namespace IonixEngine {
	class ScriptComponent : public Component {
		string scriptName;
		uint32_t objUID;
		string varName;
		Scripting* script;

	public:
		//string scriptPath = "TestProjectData/Scripts/TestScript.lua";
		// 

		//input: script name
		//script name
		//creation of script ID from uid of gameobj + script name
		//point to instance of script to attach to game object
		//check its not already being used elsewhere?
		
		const string GetScriptName() const { return scriptName; }
		
		ScriptComponent(string ScriptName);
		ScriptComponent(string ScriptName, uint32_t ObjUID);

		void OnStart();
		void OnUpdate(float deltaTime);
		void OnRender();

		void OnTriggerEnter(uint32_t uidOther);
		void OnTriggerExit(uint32_t uidOther);
		void OnCollisionEnter(uint32_t uidOther);
		void OnCollisionExit(uint32_t uidOther);

	};
}