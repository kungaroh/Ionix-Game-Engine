#pragma once
#include <lua.hpp>

namespace IonixEngine
{
	void BindInputEngineHooks(lua_State* L);
	void InitKeyBinds();
	void InitMouseBinds();
}