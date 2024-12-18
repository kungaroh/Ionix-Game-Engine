#include "EngineHooks.h"
#include "Architecture/EngineSystems.h"
#include "Components/TransformComponent.h"
#include <cinttypes>
#include <string>
#include "Logging/Console.h"
#include "Objects/Scene.h"
#include "Architecture/Application.h"
#include "Scripting/Scripting.h"
#include "Architecture/Application.h"
using namespace std;

// functions that scripts call to get/set engine state
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
	
	static int SetObjectPosition(lua_State* L)
	{
		// expects three paramters, object id, x, y
		int n = lua_gettop(L);
		if (n != 3 || !(lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)))
		{
			lua_pushliteral(L, "incorrect arguments - setobjectposition");
			lua_error(L);
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float x = lua_tonumber(L, 2);
			float y = lua_tonumber(L, 3);

			// set the position here		
			Object *o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				TransformComponent* tc = o->GetComponentOfType<TransformComponent>();
				if (tc != nullptr)
				{
					tc->x = x;
					tc->y = y;
				}
			}
		}
		return 0;
	}
	
	static int SetObjectRotation(lua_State* L) 
	{
		// expects two parameters, object id, rotation
		int n = lua_gettop(L);
		if (n != 2 || !lua_isnumber(L, 1) && lua_isnumber(L, 2))
		{
			lua_pushliteral(L, "incorrect arguments - setobjectrotation");
			lua_error(L);
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float rotation = lua_tonumber(L, 2);

			//set object rotation
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				TransformComponent* tc = o->GetComponentOfType<TransformComponent>();
				if (tc != nullptr)
				{
					tc->angle = rotation;
				}
			}
		}

		return 0;
	}

	static int SetObjectScale(lua_State* L)
	{
		// expects three paramters, object id, x, y
		int n = lua_gettop(L);
		if (n != 3 || !(lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)))
		{
			lua_pushliteral(L, "incorrect arguments - setobjectposition");
			lua_error(L);
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float sx = lua_tonumber(L, 2);
			float sy = lua_tonumber(L, 3);

			// set the position here		
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				TransformComponent* tc = o->GetComponentOfType<TransformComponent>();
				if (tc != nullptr)
				{
					tc->sx = sx;
					tc->sy = sy;
				}
			}
		}
		return 0;
	}

	static int GetObjectPosition(lua_State* L)
	{
		// expects one parameter, object uid (number)
		int n = lua_gettop(L);
		double x = 0;
		double y = 0;
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "incorrect arguments - getobjectposition");
			lua_error(L);
		}
		else
		{
			uint32_t uid = lua_tonumber(L, 1);

			// fill in x and y here from the engine
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				TransformComponent* tc = o->GetComponentOfType<TransformComponent>();
				if (tc != nullptr)
				{
					x = tc->x;
					y = tc->y;
				}
			}
		}
		// put the two return values on the stack
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		return 2;
	}



	static int GetObjectRotation(lua_State* L)
	{
		// expects one parameter, object uid (number)
		int n = lua_gettop(L);
		double angle = 0;
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "incorrect arguments - getobjectposition");
			lua_error(L);
		}
		else
		{
			uint32_t uid = lua_tonumber(L, 1);

			// fill in angle here from the engine
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				TransformComponent* tc = o->GetComponentOfType<TransformComponent>();
				if (tc != nullptr)
				{
					angle = tc->angle;
				}
			}
		}
		// put the return value on the stack
		lua_pushnumber(L, angle);
		return 1;
	}

	static int GetObjectScale(lua_State* L)
	{
		// expects one parameter, object uid (number)
		int n = lua_gettop(L);
		double sx = 0;
		double sy = 0;
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "incorrect arguments - getobjectposition");
			lua_error(L);
		}
		else
		{
			uint32_t uid = lua_tonumber(L, 1);

			// fill in x and y here from the engine
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				TransformComponent* tc = o->GetComponentOfType<TransformComponent>();
				if (tc != nullptr)
				{
					sx = tc->sx;
					sy = tc->sy;
				}
			}
		}
		// put the two return values on the stack
		lua_pushnumber(L, sx);
		lua_pushnumber(L, sy);
		return 2;
	}

	static int Instantiate(lua_State* L)
	{
		// expects two parameters, object uid (number) and new unique uid (number) to give to the clone
		int n = lua_gettop(L);

		if (n == 3)
		{
			if (!lua_isnumber(L, 1))
			{
				const char* gameObject = lua_tostring(L, 1);
				int xPos = lua_tonumber(L, 2);
				int yPos = lua_tonumber(L, 3);

				auto newGo = IonixEngine::Application::Get().layerObject->GetScene()->InstantiateAtPosition(gameObject, xPos, yPos);
				auto newName = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(newGo)->GetGameObjectName();

				lua_pushstring(L, newName.c_str());
				lua_pushnumber(L, xPos);
				lua_pushnumber(L, yPos);
				return 3;
			}
			else
			{
				uint32_t uid = lua_tonumber(L, 1);
				int xPos = lua_tonumber(L, 2);
				int yPos = lua_tonumber(L, 3);

				uint32_t newuid = IonixEngine::Application::Get().layerObject->GetScene()->InstantiateAtPosition(uid, xPos, yPos);

				lua_pushnumber(L, newuid);
				lua_pushnumber(L, xPos);
				lua_pushnumber(L, yPos);
				return 3;
			}
		}

		return -1;
	}


	static int DisableObject(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "invalid UID");
		}
		else
		{
			if (lua_isinteger(L, 1))
			{
				int uid = lua_tonumber(L, 1);
				Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
				if (o != nullptr)
					o->DisableObject();
			}
		}
		return -1;
	}
	static int EnableObject(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "invalid UID");
		}
		else
		{
			int uid = lua_tonumber(L, 1);
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
				o->EnableObject();
		}
		return -1;
	}

	static int IsObjectEnabled(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "invalid UID");
		}
		else
		{
			int uid = lua_tonumber(L, 1);
			Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				lua_pushboolean(L, o->IsEnabled());
				return 1;
			}
		}
		return 0;
	}
	static int RemoveObject(lua_State* L)
	{
		int n = lua_gettop(L);

		if (n == 1) 
		{
			if (lua_isnumber(L, 1))
			{
				uint32_t uid = lua_tonumber(L, 1);
				Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
				IonixEngine::Application::Get().layerObject->GetScene()->MarkForDelete(o);
				
			}
			else if (lua_isstring(L, 1))
			{
				const char* objName = lua_tostring(L, 1);
				Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(IonixEngine::Application::Get().layerObject->GetScene()->GetUIDByName(objName));
				IonixEngine::Application::Get().layerObject->GetScene()->MarkForDelete(o);
			}
		}
		else
		{
			lua_pushliteral(L, "Expects - object UID");
			lua_error(L);
		}

		return 0;
	}

	static int GetUidFromName(lua_State* L)
	{
		// expects two parameters, object uid (number) and new unique uid (number) to give to the clone
		int n = lua_gettop(L);

		if (n == 1)
		{
			if (lua_isstring(L, 1))
			{
				const char* gameObject = lua_tostring(L, 1);

				uint32_t uid = IonixEngine::Application::Get().layerObject->GetScene()->GetUIDByName(gameObject);

				lua_pushnumber(L, uid);
				return 1;
			}
		}

		return -1;
	}

	static int ChangeGameObjectName(lua_State* L)
	{
		int n = lua_gettop(L);

		if (n == 2)
		{
			if (lua_isnumber(L, 1))
			{
				uint32_t uid= lua_tonumber(L, 1);
				const char* newName= lua_tostring(L, 2);

				IonixEngine::Application::Get().layerObject->GetScene()->SetObjectName(uid, newName);

				lua_pushinteger(L, uid);
				lua_pushstring(L, newName);
				return 2;
			}
		}

		return -1;
	}

	static int GetObjectName(lua_State* L)
	{
		int n = lua_gettop(L);

		if (n != 1 || !lua_isinteger(L, 1))
		{
			lua_pushliteral(L, "Expects - object UID");
			lua_error(L);
		}

		uint32_t uid = lua_tonumber(L, 1);

		string name = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid)->GetGameObjectName();

		lua_pushstring(L, name.c_str());

		return 1;
	}

	static int GetObjectTag(lua_State* L)
	{
		int n = lua_gettop(L);

		if (n == 1)
		{
			if (lua_isnumber(L, 1))
			{
				uint32_t uid = lua_tonumber(L, 1);

				Object* o = IonixEngine::Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
				string tag = o->GetTag();

				lua_pushstring(L, tag.c_str());
				return 1;
			}
		}
		return -1;
	}

	static int ReturnIntArray(lua_State* L) {
		std::vector<int> dynamicArray = { 1, 2, 3, 4, 5, 6, 7,100 };
		lua_createtable(L, dynamicArray.size(), 0); // Create a new table

		for (size_t i = 0; i < dynamicArray.size(); ++i) {
			lua_pushinteger(L, dynamicArray[i]);   // Push value
			lua_rawseti(L, -2, i + 1);             // Set value at index (1-based)
		}

		return 1; // Return the table
	}
} // extern "C"

namespace IonixEngine
{
	//Signitures for other engine hooks
	extern void BindScriptingEngineHooks(lua_State* L);
	extern void BindAudioEngineHooks(lua_State* L);
	extern void BindPhysicsEngineHooks(lua_State* L);
	extern void BindLibraryEngineHooks(lua_State* L);
	extern void BindGraphicsEngineHooks(lua_State* L);
	extern void BindUIEngineHooks(lua_State* L);
	extern void BindInputEngineHooks(lua_State* L);


	// helpers
	double GetGlobalNumberValue(lua_State* L, const std::string& varName)
	{
		lua_getglobal(L, varName.c_str());
		if (lua_isnumber(L, -1))
		{
			return lua_tonumber(L, -1);
		}
		return 0.0;
	}

	string GetGlobalStringValue(lua_State* L, const std::string& varName)
	{
		lua_getglobal(L, varName.c_str());
		if (lua_isstring(L, -1))
		{
			return lua_tostring(L, -1);
		}
		return "";
	}

	double GetNumberValueFromTable(lua_State* L, const std::string& tableName, const std::string& element)
	{
		lua_getglobal(L, tableName.c_str());
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, element.c_str());
			lua_gettable(L, -2); // get tableName[element]
			if (lua_isnumber(L, -1))
				return lua_tonumber(L, -1);
		}
		return 0.0;
	}

	string GetStringValueFromTable(lua_State* L, const std::string& tableName, const std::string& element)
	{
		lua_getglobal(L, tableName.c_str());
		if (lua_istable(L, -1))
		{
			lua_pushstring(L, element.c_str());
			lua_gettable(L, -2); // get tableName[element]
			if (lua_isstring(L, -1))
				return lua_tostring(L, -1);
		}
		return string();
	}

	bool TableExists(lua_State* L, const std::string& tableName)
	{
		lua_getglobal(L, tableName.c_str());
		return lua_istable(L, -1);
	}

	// add a C function to the Lua VM, and bind it to a global name.
	void BindFunction(lua_State* L, lua_CFunction func, const string& luaName)
	{
		lua_pushcfunction(L, func);
		lua_setglobal(L, luaName.c_str());
	}

	void BindAllEngineHooks(lua_State* L)
	{
		BindFunction(L, SetObjectPosition, "set_object_position"); // arguments: uid(num), x (num), y(num), returns : void
		BindFunction(L, GetObjectPosition, "get_object_position"); // arguments: uid(num), returns: x(num), y(num)
		BindFunction(L, SetObjectRotation, "set_object_rotation"); // arguments: uid(num), angle (num), returns : void
		BindFunction(L, GetObjectRotation, "get_object_rotation"); // arguments: uid(num), returns: angle(num)
		BindFunction(L, SetObjectScale, "set_object_scale"); // arguments: uid(num), sx(num), sy(num), returns: void
		BindFunction(L, GetObjectScale, "get_object_scale"); // arguments: uid(num), returns:  sx(num), sy(num)
		BindFunction(L, Instantiate, "instantiate"); // expects 2 or 4 arguments
		BindFunction(L, GetUidFromName, "uid_from_name"); // expects 1
		BindFunction(L, ChangeGameObjectName, "change_gameObject_name"); // expects 2
		BindFunction(L, DisableObject, "disable_object"); // expects 1 expects object UID
		BindFunction(L, EnableObject, "enable_object"); // expects 1 expects object UID
		BindFunction(L, IsObjectEnabled, "is_enabled"); // expects 1 expects object UID, returns bool
		BindFunction(L, RemoveObject, "remove_object"); //UID
		BindFunction(L, GetObjectTag, "get_object_tag"); //UID
		BindFunction(L, GetObjectName, "get_object_name"); //UID
		BindFunction(L, ReturnIntArray, "return_int_array");

		//Scripting
		BindScriptingEngineHooks(L);

		//Physics
		BindPhysicsEngineHooks(L);

		//Audio
		BindAudioEngineHooks(L);

		//Graphics
		BindGraphicsEngineHooks(L);
		
		//UI
		BindUIEngineHooks(L);

		//Input
		BindInputEngineHooks(L);

		//Library
		BindLibraryEngineHooks(L);
	}
}
