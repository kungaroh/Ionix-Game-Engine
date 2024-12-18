#include "EngineHooksInput.h"
#include "Logging/Console.h"
#include "../Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include <string>
#include "Input/input.h"
#include <unordered_map>
#include "LayerSystem/Layers/LayerInput.h"

using namespace std;

namespace IonixEngine
{
	LayerInput* layerInput;

	unordered_map <string, Keycode> keyBinds;

	unordered_map <string, Mousecode> mouseBinds;

	void InitKeyBinds()
	{
		keyBinds["Ionix_A"] = Keycode::Ionix_A;
		keyBinds["Ionix_B"] = Keycode::Ionix_B;
		keyBinds["Ionix_C"] = Keycode::Ionix_C;
		keyBinds["Ionix_D"] = Keycode::Ionix_D;
		keyBinds["Ionix_E"] = Keycode::Ionix_E;
		keyBinds["Ionix_F"] = Keycode::Ionix_F;
		keyBinds["Ionix_G"] = Keycode::Ionix_G;
		keyBinds["Ionix_H"] = Keycode::Ionix_H;
		keyBinds["Ionix_I"] = Keycode::Ionix_I;
		keyBinds["Ionix_J"] = Keycode::Ionix_J;
		keyBinds["Ionix_K"] = Keycode::Ionix_K;
		keyBinds["Ionix_L"] = Keycode::Ionix_L;
		keyBinds["Ionix_M"] = Keycode::Ionix_M;
		keyBinds["Ionix_N"] = Keycode::Ionix_N;
		keyBinds["Ionix_O"] = Keycode::Ionix_O;
		keyBinds["Ionix_P"] = Keycode::Ionix_P;
		keyBinds["Ionix_Q"] = Keycode::Ionix_Q;
		keyBinds["Ionix_R"] = Keycode::Ionix_R;
		keyBinds["Ionix_S"] = Keycode::Ionix_S;
		keyBinds["Ionix_T"] = Keycode::Ionix_T;
		keyBinds["Ionix_U"] = Keycode::Ionix_U;
		keyBinds["Ionix_V"] = Keycode::Ionix_V;
		keyBinds["Ionix_W"] = Keycode::Ionix_W;
		keyBinds["Ionix_X"] = Keycode::Ionix_X;
		keyBinds["Ionix_Y"] = Keycode::Ionix_Y;
		keyBinds["Ionix_Z"] = Keycode::Ionix_Z;
		keyBinds["Ionix_0"] = Keycode::Ionix_0;
		keyBinds["Ionix_1"] = Keycode::Ionix_1;
		keyBinds["Ionix_2"] = Keycode::Ionix_2;
		keyBinds["Ionix_3"] = Keycode::Ionix_3;
		keyBinds["Ionix_4"] = Keycode::Ionix_4;
		keyBinds["Ionix_5"] = Keycode::Ionix_5;
		keyBinds["Ionix_6"] = Keycode::Ionix_6;
		keyBinds["Ionix_7"] = Keycode::Ionix_7;
		keyBinds["Ionix_8"] = Keycode::Ionix_8;
		keyBinds["Ionix_9"] = Keycode::Ionix_9;
		keyBinds["Ionix_Space"] = Keycode::Ionix_Space;
		keyBinds["Ionix_Return"] = Keycode::Ionix_Return;
		keyBinds["Ionix_Escape"] = Keycode::Ionix_Escape;
		keyBinds["Ionix_Tab"] = Keycode::Ionix_Tab;
		keyBinds["Ionix_Backspace"] = Keycode::Ionix_Backspace;
		keyBinds["Ionix_Delete"] = Keycode::Ionix_Delete;
		keyBinds["Ionix_Up"] = Keycode::Ionix_Up;
		keyBinds["Ionix_Down"] = Keycode::Ionix_Down;
		keyBinds["Ionix_Left"] = Keycode::Ionix_Left;
		keyBinds["Ionix_Right"] = Keycode::Ionix_Right;
		keyBinds["Ionix_LeftShift"] = Keycode::Ionix_LeftShift;
		keyBinds["Ionix_RightShift"] = Keycode::Ionix_RightShift;
		keyBinds["Ionix_LeftControl"] = Keycode::Ionix_LeftControl;
		keyBinds["Ionix_RightControl"] = Keycode::Ionix_RightControl;
		keyBinds["Ionix_LeftAlt"] = Keycode::Ionix_LeftAlt;
		keyBinds["Ionix_RightAlt"] = Keycode::Ionix_RightAlt;
		keyBinds["Ionix_CapsLock"] = Keycode::Ionix_CapsLock;
	}
	void InitMouseBinds()
	{
		mouseBinds["Ionix_LeftClick"] = Mousecode::Ionix_Mouse0;
		mouseBinds["Ionix_RightClick"] = Mousecode::Ionix_Mouse1;
		mouseBinds["Ionix_MiddleClick"] = Mousecode::Ionix_Mouse2;
	}
	
	static int IsKeyDown(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* key = lua_tostring(L, 1);

		// Check if key is in the keyBinds map
		auto it = keyBinds.find(key);
		if (it == keyBinds.end())
		{
			return luaL_error(L, "Key not registered: %s", key);
		}

		Keycode keycode = it->second;
		bool isDown = Application::Get().layerInput->m_Input->IsKeyDown(keycode);

		lua_pushboolean(L, isDown);
		return 1;
	}

	static int IsKeyHeld(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* key = lua_tostring(L, 1);

		// Check if key is in the keyBinds map
		auto it = keyBinds.find(key);
		if (it == keyBinds.end())
		{
			return luaL_error(L, "Key not registered: %s", key);
		}

		Keycode keycode = it->second;
		bool isHeld = Application::Get().layerInput->m_Input->IsKeyHeld(keycode);

		lua_pushboolean(L, isHeld);
		return 1;
	}

	static int IsKeyUp(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* key = lua_tostring(L, 1);

		// Check if key is in the keyBinds map
		auto it = keyBinds.find(key);
		if (it == keyBinds.end())
		{
			return luaL_error(L, "Key not registered: %s", key);
		}

		Keycode keycode = it->second;
		bool isUp = Application::Get().layerInput->m_Input->IsKeyUp(keycode);

		lua_pushboolean(L, isUp);
		return 1;
	}

	static int IsMouseDown(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* mouseBtn = lua_tostring(L, 1);

		Mousecode mousecode = static_cast<Mousecode>(mouseBinds[mouseBtn]);
		bool isDown = Application::Get().layerInput->m_Input->IsMouseDown(mousecode);

		lua_pushboolean(L, isDown);
		return 1;
	}

	static int IsMouseHeld(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* mouseBtn = lua_tostring(L, 1);

		Mousecode mousecode = static_cast<Mousecode>(mouseBinds[mouseBtn]);
		bool isHeld = Application::Get().layerInput->m_Input->IsMouseHeld(mousecode);

		lua_pushboolean(L, isHeld);
		return 1;
	}

	static int IsMouseUp(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isstring(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected a single string");
		}
		const char* mouseBtn = lua_tostring(L, 1);

		Mousecode mousecode = static_cast<Mousecode>(mouseBinds[mouseBtn]);
		bool isUp = Application::Get().layerInput->m_Input->IsMouseUp(mousecode);

		lua_pushboolean(L, isUp);
		return 1;
	}

	static int GetMouseX(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			return luaL_error(L, "No arguments required");
		}
		float mouseX = Application::Get().layerInput->m_Input->GetMouseX();
		lua_pushinteger(L, mouseX);
		return 1;
	}

	static int GetMouseY(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			return luaL_error(L, "No arguments required");
		}
		float mouseY = Application::Get().layerInput->m_Input->GetMouseY();
		lua_pushinteger(L, mouseY);
		return 1;
	}

	void BindInputEngineHooks(lua_State* L)
	{
		//KeyBinds
		BindFunction(L, IsKeyDown, "is_key_down");
		BindFunction(L, IsKeyHeld, "is_key_held");
		BindFunction(L, IsKeyUp, "is_key_up");

		//MouseBinds
		BindFunction(L, IsMouseDown, "is_mouse_down");
		BindFunction(L, IsMouseHeld, "is_mouse_held");
		BindFunction(L, IsMouseUp, "is_mouse_up");

		//Get Mouse Pos
		BindFunction(L, GetMouseX, "get_mouse_x");
		BindFunction(L, GetMouseY, "get_mouse_y");
	}
}