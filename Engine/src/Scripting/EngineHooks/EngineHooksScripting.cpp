#include "EngineHooksScripting.h"
#include "Logging/Console.h"
#include "../Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include <string>
using namespace std;

namespace IonixEngine
{
	LayerScripting* layerScripting;

	static int Log(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* Output = lua_tostring(L, 1);
		Console::info(Output);
		return 0;
	}

	static int LogError(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* Output = lua_tostring(L, 1);
		Console::error(Output);
		return 0;
	}

	static int LogWarning(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* Output = lua_tostring(L, 1);
		Console::warning(Output);
		return 0;
	}

	static int CallFunc(lua_State* L)
	{
		//arguments: string ScriptToFind, string Function, uint32_t Object

		int n = lua_gettop(L);
		if (n != 3 || !(lua_isstring(L, 1) && lua_isstring(L, 2) && lua_isnumber(L, 3)))
		{
			lua_pushliteral(L, "incorrect arguments - Call_Function");
			lua_error(L);
		}
		else
		{
			string ScriptToFind = lua_tostring(L, 1);
			string Function = lua_tostring(L, 2);
			uint32_t Object = (uint32_t)lua_tonumber(L, 3);
			Scripting* script = Application::Get().layerScripting->GetScripting();
			string code = (ScriptToFind + "_" + to_string(Object)) + ":" + Function + "()";
			string message = TableExists(L, ScriptToFind + "_" + to_string(Object)) ? "found" : "not found";
			//Console::info(message);
			script->ExecuteLuaCode(code);
		}
		return 0;
	}

	//################		Tiled Import		###################//

	static int MapImportTileSize(lua_State* L)
	{

		int n = lua_gettop(L);
		if (n != 4)
		{
			lua_pushliteral(L, "incorrect arguments - MapImportTileSize");
			lua_error(L);
		}
		else
		{
			float x = lua_tonumber(L, 1);
			float y = lua_tonumber(L, 2);
			float xMapSize = lua_tonumber(L, 3);
			float yMapSize = lua_tonumber(L, 4);

			const char* name = lua_tostring(L, 6);
			Application::Get().layerScripting->GetScripting()->MapTileSizeImport(x, y, xMapSize, yMapSize);
		}
		return 0;
	}

	static int MapVariableImport(lua_State* L) 
	{
		//arguments: x,y,width,height,visible,name

		int n = lua_gettop(L);
		if (n != 7 || !(lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4) && lua_isboolean(L, 5) && lua_isstring(L, 6) && lua_isnumber(L, 7)))
		{
			lua_pushliteral(L, "incorrect arguments - Map variable import");
			lua_error(L);
		}
		else 
		{
			float x = lua_tonumber(L, 1);
			float y = lua_tonumber(L, 2);
			float width = lua_tonumber(L, 3);
			float height = lua_tonumber(L, 4);
			bool visible = lua_toboolean(L, 5);
			const char* name = lua_tostring(L, 6);
			int gid = lua_tonumber(L, 7);
			Application::Get().layerScripting->GetScripting()->MapVariableImport(x,y,width,height,visible,name,gid);
		}
		return 0;
	}

	static int ObjectProperties(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isstring(L, 1) && lua_isstring(L, 2)))
		{
			lua_pushliteral(L, "Incorrect arguments - Expects Key & Value!");
			lua_error(L);
		}
		else
		{
			const char* key = lua_tostring(L, 1);
			const char* value = lua_tostring(L, 2);
			Application::Get().layerScripting->GetScripting()->ObjectProperties(key, value);
		}
		return 0;
	}

	static int AddObjectToLayer(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			lua_pushliteral(L, "Incorrect arguments - Expects none");
			lua_error(L);
		}
		else
		{
			Application::Get().layerScripting->GetScripting()->AddObjectToLayer();
		}
		return 0;
	}

	static int AddTileMapIDData(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isinteger(L, 1))
		{
			lua_pushliteral(L, "Incorrect arguments - Expects tile map ID data");
			lua_error(L);
		}

		int data = lua_tointeger(L, 1);

		Application::Get().layerScripting->GetScripting()->AddTileMapIDData(data);

		return 0;
	}

	static int MapLayerImport(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isstring(L, 1))
		{
			lua_pushliteral(L, "Incorrect arguments - Expects layer name");
			lua_error(L);
		}

		const char* name = lua_tostring(L, 1);

		Application::Get().layerScripting->GetScripting()->MapLayerImport( (string)name );

		return 0;
	}

	static int LayerProperties(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isstring(L, 1) && lua_isstring(L, 2)))
		{
			lua_pushliteral(L, "Incorrect arguments - Expects Key & Value!");
			lua_error(L);
		}
		else
		{
			const char* key = lua_tostring(L, 1);
			const char* value = lua_tostring(L, 2);
			Application::Get().layerScripting->GetScripting()->LayerProperties(key, value);
		}

		return 0;
	}

	static int AddLayerToData(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			lua_pushliteral(L, "Incorrect arguments - Expects none");
			lua_error(L);
		}
		else
		{
			Application::Get().layerScripting->GetScripting()->AddLayerToData();
		}
		return 0;
	}

	static int TileSetImport(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isinteger(L, 1) && lua_isstring(L, 2)))
		{
			lua_pushliteral(L, "Incorrect arguments - Expects firstgid & filename!");
			lua_error(L);
		}
		else
		{
			int firstgid = lua_tointeger(L, 1);
			const char* filename = lua_tostring(L, 2);
			Application::Get().layerScripting->GetScripting()->TileSetImport(firstgid, (string)filename);
		}
		return 0;
	}

	static int CallTiledImportEvent(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			lua_pushliteral(L, "Incorrect arguments - Expects none");
			lua_error(L);
		}
		else
		{
			Application::Get().layerScripting->GetScripting()->CallTiledImportEvent();
		}
		return 0;
	}

	void BindScriptingEngineHooks(lua_State* L)
	{
		BindFunction(L, CallFunc, "call_function");                //arguments: string ScriptToFind, string Function, uint32_t Object
		// Console
		BindFunction(L, Log, "log");
		BindFunction(L, LogError, "log_error");
		BindFunction(L, LogWarning, "log_warning");

		//Tiled Object
		BindFunction(L, MapVariableImport, "map_variable_import");
		BindFunction(L, MapImportTileSize, "map_tile_size_import");
		BindFunction(L, ObjectProperties, "object_properties");

		//Tiled Layer
		BindFunction(L, AddObjectToLayer, "add_object_to_layer");
		BindFunction(L, AddTileMapIDData, "add_tile_map_id_data");
		BindFunction(L, MapLayerImport, "map_layer_import");
		BindFunction(L, LayerProperties, "layer_properties");
		BindFunction(L, AddLayerToData, "add_layer_to_data");

		//Tiled Set
		BindFunction(L, TileSetImport, "tile_set_import");
		
		//Tiled Events
		BindFunction(L, CallTiledImportEvent, "call_tiled_import_event");
	}
}