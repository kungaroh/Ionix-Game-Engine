#include "Components/ScriptComponent.h"
#include "Architecture/Application.h"

namespace IonixEngine {
	//all guesswork basically
	void ScriptComponent::OnStart(){
		//loads the script into the already intiated
		//virutal machine
		objUID = GetOwner()->UID();

		script->LoadScript(scriptName);
		varName = scriptName + "_" + to_string(objUID);
		script->InstantiateScript(varName, scriptName);
		// give the script a way to access the parent object UID
		script->ExecuteLuaCode(varName + ".__uid = " + to_string(objUID));
		script->ExecuteLuaCode(varName + ".__objName = " + GetOwner()->GetGameObjectName());
		script->ExecuteLuaCode(varName + ":OnStart()");

	}
	void ScriptComponent::OnUpdate(float deltatime){
		//should execute the code for the selected scripts  
		//on update (that should work every frame)
		script->ExecuteLuaCode(varName + ":OnUpdate(" + to_string(deltatime) + ")");
	}

	void ScriptComponent::OnRender(){


	}

	void ScriptComponent::OnTriggerEnter(uint32_t uidOther)
	{
		string code = "if " + varName + ".OnTriggerEnter ~= nil then " + varName + ":OnTriggerEnter(" + to_string(uidOther) + ") end";
		script->ExecuteLuaCode(code);
	}

	void ScriptComponent::OnTriggerExit(uint32_t uidOther)
	{
		string code = "if " + varName + ".OnTriggerExit ~= nil then " + varName + ":OnTriggerExit(" + to_string(uidOther) + ") end";
		script->ExecuteLuaCode(code);
	}

	void ScriptComponent::OnCollisionEnter(uint32_t uidOther)
	{
		string code = "if " + varName + ".OnCollisionEnter ~= nil then " + varName + ":OnCollisionEnter(" + to_string(uidOther) + ") end";
		script->ExecuteLuaCode(code);
	}

	void ScriptComponent::OnCollisionExit(uint32_t uidOther)
	{
		string code = "if " + varName + ".OnCollisionExit ~= nil then " + varName + ":OnCollisionExit(" + to_string(uidOther) + ") end";
		script->ExecuteLuaCode(code);
	}




	ScriptComponent::ScriptComponent(string ScriptName) : Component("Script")
	{

		script = Application::Get().layerScripting->GetScripting();

		scriptName = ScriptName;
	}
	ScriptComponent::ScriptComponent(string ScriptName, uint32_t ObjUID) : Component("Script")
	{

		script = Application::Get().layerScripting->GetScripting();

		objUID = ObjUID;
		scriptName = ScriptName;
	}

}