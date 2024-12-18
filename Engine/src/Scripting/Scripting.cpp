#include <fstream>
#include <sstream>

#include "..\Scripting\Scripting.h" 
#include "..\Architecture\EngineSystems.h"
#include "EngineHooks/EngineHooks.h"
#include "Logging/Console.h"
#include "ResourceManager.h"
#include <EventSystem/Events/EventDefinitions.h>
#include "Architecture/Application.h"

static string MakeNewFn(string objectName)
{
	return "function " + objectName + ".new(self)\n o = {}\n setmetatable(o, self)\n self.__index = self\n return o\n end\n";
}

// code replaces 'return' with 'map_import =' TECHNICALLY DONE
// ExecuteLuaCode on that string - now vm has a table called map_import TECHNICALLY DONE
// then ExecuteLuaCode("import_from_map(map_import)");
namespace IonixEngine
{
	int Scripting::LoadScript(string scriptName)
	{
		// load script if is it not already loaded
		if (!TableExists(luaState, scriptName))
		{
			string fileName = IonixEngine::EngineSystems::ProjectPath() + "\\Scripts\\" + scriptName + ".lua";
			fstream in_file = fstream(fileName);
			if (in_file.is_open())
			{
				std::stringstream buffer;
				buffer << in_file.rdbuf();
				string scriptText = buffer.str();
				// add the new function
				scriptText += "\n" + MakeNewFn(scriptName);
				ExecuteLuaCode(scriptText);
				return 1;
			}
			return 0;
		}
		return 1;
	}	

	void Scripting::InstantiateScript(string varName, string scriptName)
	{
		string script = varName + " = " + scriptName + ":new()\n";
		ExecuteLuaCode(script);
	}

	Scripting::Scripting()
	{
		InitLua();
		BindAllEngineHooks(luaState);

		// load std library
		string fileName = IonixEngine::EngineSystems::ProjectPath() + "\\Scripts\\stdlib.lua";
		fstream in_file = fstream(fileName);
		if (in_file.is_open())
		{
			std::stringstream buffer;
			buffer << in_file.rdbuf();
			string scriptText = buffer.str();
			ExecuteLuaCode(scriptText);
			in_file.close();
		}
	}

	void Scripting::SetVarNumber(string varName, double varValue)
	{
		string script = varName + " = " + to_string(varValue) + "\n";
		ExecuteLuaCode(script);
	}
	void Scripting::SetVarString(string varName, string varValue)
	{
		string script = varName + " = " + varValue + "\n";
		ExecuteLuaCode(script);
	}
	double Scripting::GetVarNumber(string varName)
	{
		return GetGlobalNumberValue(luaState, varName);
	}
	string Scripting::GetVarString(string varName)
	{
		return GetGlobalStringValue(luaState, varName);
	}


	//#######################		Tiled Import		#############################//

	TiledObject tiledObject;
	TiledLayer tiledLayer;
	TiledSet tiledSet;
	TiledData tiledData;

	TiledData Scripting::GetTiledData()
	{
		return tiledData;
	}

	int Scripting::MapImport() 
	{
		string fileName = ResourceManager::GetInstance().EDITOR_PATH + "GameEngineTileMap.lua";
		fstream in_file = fstream(fileName);

		if (in_file.is_open())
		{
			std::stringstream buffer;
			buffer << in_file.rdbuf();
			string mapText = buffer.str();
			mapText = "map_import = " + string( mapText.c_str()+7 );

			//mapText = "map_import = { version = 3 }";
			ExecuteLuaCode(mapText); //adds to the virtual machine
			ExecuteLuaCode("import_from_map(map_import)"); //Current mad line
			in_file.close();
			return 1;
		}
	}

	void Scripting::MapVariableImport(float x, float y, float width, float height, bool visible, const char* name, int gid) 
	{
		tiledObject.properties.clear();
		string message = "Map Variable Import: " + to_string(x) + " " + to_string(y) + " " + to_string(width) + " " + to_string(height) + " " + to_string(visible) + " " + name;
		//Console::info(message);
		tiledObject.name = name;
		tiledObject.x = x;
		tiledObject.y = y;
		tiledObject.width = width;
		tiledObject.height = height;
		tiledObject.visible = visible;
		tiledObject.gid = gid;
	}

	void Scripting::MapTileSizeImport(float x, float y, float mapWidth, float mapHeight)
	{		
		tiledData.tileWidth = x;
		tiledData.tileHeight = y;
		tiledData.mapWidth = mapWidth;
		tiledData.mapHeight = mapHeight;
	}

	void Scripting::ObjectProperties(string key, string value)
	{
		string message = "Object Properties: " + key + " " + value;
		//Console::info(message);
		tiledObject.properties[key] = value;
	}

	void Scripting::AddObjectToLayer()
	{
		tiledLayer.tiledObjects.push_back(tiledObject);
	}
	
	void Scripting::MapLayerImport(string name)
	{
		tiledLayer.tilemapIDdata.clear();
		tiledLayer.properties.clear();
		tiledLayer.tiledObjects.clear();
		tiledLayer.name = name;
	}

	void Scripting::LayerProperties(string key, string value)
	{
		tiledLayer.properties[key] = value;
	}
	
	void Scripting::AddTileMapIDData(int data)
	{
		tiledLayer.tilemapIDdata.push_back(data);
	}

	void Scripting::AddLayerToData()
	{
		tiledData.tiledLayers.push_back(tiledLayer);
	}

	void Scripting::TileSetImport(int firstgid, string filename)
	{
		tiledSet.firstgid = firstgid;
		tiledSet.filename = filename;
		tiledData.tiledSets.push_back(tiledSet);
	}

	void Scripting::CallTiledImportEvent()
	{
		Event_OnTileMapDataLoaded e(tiledData);
		Application::Get().GetWindow().m_Data.EventCallback(e);
	}
}