#pragma once 
#include <lua.hpp>
#include <string>

namespace IonixEngine
{
	double GetGlobalNumberValue(lua_State* L, const std::string& varName);
	std::string GetGlobalStringValue(lua_State* L, const std::string& varName);
	double GetNumberValueFromTable(lua_State* L, const std::string& tableName, const std::string& element);
	std::string GetStringValueFromTable(lua_State* L, const std::string& tableName, const std::string& element);
	bool TableExists(lua_State* L, const std::string& tableName);
	void BindFunction(lua_State* L, lua_CFunction func, const std::string& luaName);
	void BindAllEngineHooks(lua_State* L);
}
