#pragma once 
#include <string>
#include <iostream>
#include "Logging/Console.h"
#include <sstream>
#include <unordered_map>

using namespace std;

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
};

namespace IonixEngine
{
	struct TiledObject {
		const char* name;
		float x;
		float y;
		float width;
		float height;
		bool visible;
		int gid;
		std::unordered_map<std::string, std::string> properties;
	};

	struct TiledLayer {
		string name;
		vector<int> tilemapIDdata;
		vector<TiledObject> tiledObjects;
		std::unordered_map<std::string, std::string> properties;
	};

	struct TiledSet {
		int firstgid;
		string filename;
	};

	struct TiledData {
		int tileWidth;
		int tileHeight;
		int mapWidth;
		int mapHeight;
		vector<TiledLayer> tiledLayers;
		vector<TiledSet> tiledSets;
	};

	class Scripting
	{
		// global lua state - this is the virtual machine
		lua_State* luaState;
		
		void InitLua()
		{
			luaState = luaL_newstate();
			luaL_openlibs(luaState);
		}
		void CloseLua()
		{
			lua_close(luaState);
		}

	public:
		Scripting();
		~Scripting()
		{
			CloseLua();
		}

		inline lua_State* GetLuaState() { return luaState;  }

		int ExecuteLuaCode(const std::string& code)
		{
			int error = luaL_loadstring(luaState, code.c_str()) || lua_pcall(luaState, 0, 0, 0);

			if (error) {
				const char* errorMessage = lua_tostring(luaState, -1);
				stringstream ss;
				ss << "Lua error: " << errorMessage;
				Console::error(ss.str());
				lua_pop(luaState, 1);
			}
			return error;
		}

		int LoadScript(string scriptName);
		int MapImport();
		void InstantiateScript(string varName, string scriptName);


		void SetVarNumber(string varName, double varValue);
		void SetVarString(string varName, string varValue);
		double GetVarNumber(string varName);
		string GetVarString(string varName);

		void AddTileMapIDData(int data);
		void AddLayerToData();
		void MapLayerImport(string name);
		void LayerProperties(string key, string value);
		void MapVariableImport(float x, float y, float width, float height, bool visible, const char* name, int gid);
		void MapTileSizeImport(float x, float y, float mapWidth, float mapHeight);
		void ObjectProperties(string key, string value);
		void AddObjectToLayer();
		void TileSetImport(int firstgid, string filename);
		void CallTiledImportEvent();

		TiledData GetTiledData();
	};
}