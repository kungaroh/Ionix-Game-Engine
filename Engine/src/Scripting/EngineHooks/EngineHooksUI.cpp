#include "EngineHooksUI.h"
#include "Logging/Console.h"
#include "../Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include <string>
using namespace std;

namespace IonixEngine
{

	//AddLabel
	//AddButton
	//GetButtonState
	//SetGroupPosistion

	int IsButtonPressed(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			return luaL_error(L, "Incorrect arguments - expected UI ID");
		}

		int id = lua_tointeger(L, 1);
		bool val = Application::Get().layerUI->GetUIManager()->uiQueue->GetButtonPressed(id);

		lua_pushboolean(L, val);
		return 1;
	}


	int AddLabel(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 5 || !(lua_isstring(L, 1)) || !(lua_isinteger(L, 2)) || !(lua_isinteger(L, 3)) || !(lua_isinteger(L, 4)) || !(lua_isinteger(L, 5)))
		{
			return luaL_error(L, "Incorrect arguments - expected text, x, y, givenID, groupID");
		}
		const char* text = lua_tostring(L, 1);
		int x = lua_tointeger(L, 2);
		int y = lua_tointeger(L, 3);
		int givenID = lua_tointeger(L, 4);
		int groupID = lua_tointeger(L, 5);

		Application::Get().layerUI->GetUIManager()->uiQueue->AddLabel(text, x, y, givenID, groupID);

		return 0;
	}

	int AddButton(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 7 || !(lua_isstring(L, 1)) || !(lua_isinteger(L, 2)) || !(lua_isinteger(L, 3)) || !(lua_isinteger(L, 4)) || !(lua_isinteger(L, 5)) || !(lua_isinteger(L, 6)) || !(lua_isinteger(L, 7)))
		{
			return luaL_error(L, "Incorrect arguments - expected text, x, y, sizeX, sizeY, givenID, groupID");
		}

		const char* text = lua_tostring(L, 1);
		int x = lua_tointeger(L, 2);
		int y = lua_tointeger(L, 3);
		int sizeX = lua_tointeger(L, 4);
		int sizeY = lua_tointeger(L, 5);
		int givenID = lua_tointeger(L, 6);
		int groupID = lua_tointeger(L, 7);

		Application::Get().layerUI->GetUIManager()->uiQueue->AddButton(text, x, y, sizeX, sizeY, givenID, groupID);

		return 0;
	}

	int ChangeTextUI(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isinteger(L, 1)) || !(lua_isstring(L, 2)))
		{
			return luaL_error(L, "Incorrect arguments - expected ui element ID, text");
		}

		int id = lua_tointeger(L, 1);
		const char* text = lua_tostring(L, 2);

		Application::Get().layerUI->GetUIManager()->uiQueue->UpdateTextUI(id, text);

		return 0;
	}

	int SetActive(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isinteger(L, 1)) || !(lua_isboolean(L, 2)))
		{
			return luaL_error(L, "Incorrect arguments - expected ui element ID, bool");
		}

		int id = lua_tointeger(L, 1);
		bool val = lua_toboolean(L, 2);

		Application::Get().layerUI->GetUIManager()->uiQueue->SetActiveUI(id, val);

		return 0;
	}

	int SetGroupPosition(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 3 || !(lua_isinteger(L, 1)) || !(lua_isinteger(L, 2) || !(lua_isinteger(L, 3))))
		{
			return luaL_error(L, "Incorrect arguments - expected ID, x, y");
		}

		int ID = lua_tointeger(L, 1);
		int x = lua_tointeger(L, 2);
		int y = lua_tointeger(L, 3);

		Application::Get().layerUI->GetUIManager()->uiGroup->setGroupPosition(ID, x, y);

		return 0;
	}

	void BindUIEngineHooks(lua_State* L) {
		BindFunction(L, AddLabel, "add_label");
		BindFunction(L, AddButton, "add_button");
		BindFunction(L, IsButtonPressed, "is_button_pressed");
		BindFunction(L, SetGroupPosition, "set_group_position");
		BindFunction(L, ChangeTextUI, "update_ui_text");
		BindFunction(L, SetActive, "set_active");
	}
}