#pragma once
#include <lua.hpp>
#include "graphics/Graphics.h"

namespace IonixEngine
{
	Graphics* graphics;
	void BindGraphicsEngineHooks(lua_State* L);
}
