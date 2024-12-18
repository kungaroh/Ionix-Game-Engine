#include "EngineHooksGraphics.h"
#include "Logging/Console.h"
#include "../Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include "Components/SpriteComponent.h"
#include <string>
using namespace std;

namespace IonixEngine
{
	//may not use these ones that make more sense: enable/disable for draw sprite and playing animation

	static int DrawSprites(lua_State* L)
	{
		//arguments: Sprite sprite,
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isuserdata(L, 1)))
		{
			lua_pushliteral(L, "incorrect arguments - Draw_Sprites");
			lua_error(L);
		}
		else
		{
			Sprite* sprite = *(Sprite**)lua_touserdata(L, 1);
			//graphics.DrawSprite(*sprite);			
		}
		return 0;
		//void Graphics::DrawSprite(Sprite& sprite)
	}

	/*static int CallFunc(lua_State* L)
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
			string code = (ScriptToFind + "_" + to_string(Object)) + Function;
			string message = TableExists(L, ScriptToFind + "_" + to_string(Object)) ? "found" : "not found";
			Console::info(message);
			script->ExecuteLuaCode(code);
		}
		return 0;
	}*/

	static int SetTexture(lua_State* L)
	{
		// arguments - uid (number), texturefilename (string)

		int n = lua_gettop(L);
		if (n != 2 || !(lua_isnumber(L, 1) && lua_isstring(L, 2)))
		{
			lua_pushliteral(L, "incorrect arguments - SetTexture");
			lua_error(L);
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1); 
			string texture = lua_tostring(L, 2);
			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				SpriteComponent* sc = o->GetComponentOfType<SpriteComponent>();
				if (sc != nullptr)
				{
					sc->UpdateTexture(texture);
				}
			}
		}

		return 0;
	}

	static int SetAnimationParams(lua_State* L)
	{
		// arguments - uid (number), num_animation_rows, num_animation_frames, cur_animation_row, speed
		int n = lua_gettop(L);
		if (n != 5 || !(lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3) && lua_isnumber(L, 4) && lua_isnumber(L, 5)))
		{
			lua_pushliteral(L, "incorrect arguments - SetAnimationParams");
			lua_error(L);
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			uint32_t nRows = (uint32_t)lua_tonumber(L, 2);
			uint32_t nFrames = (uint32_t)lua_tonumber(L, 3);
			uint32_t curRow = (uint32_t)lua_tonumber(L, 4);
			float speed = (uint32_t)lua_tonumber(L, 5);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				SpriteComponent* sc = o->GetComponentOfType<SpriteComponent>();
				if (sc != nullptr)
				{
					sc->SetAnimationRows(nRows);
					sc->SetAnimationFrames(nFrames);
					sc->SetCurrentAnimationRow(curRow);
					sc->SetAnimationSpeed(speed);
				}
			}
		}
		return 0;
	}

	static int SetCameraPos(lua_State* L)
	{
		// arguments - x, y
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isnumber(L, 1) && lua_isnumber(L, 2) ))
		{
			lua_pushliteral(L, "incorrect arguments - SetCameraPos");
			lua_error(L);
		}
		else
		{
			float x = lua_tonumber(L, 1);
			float y = lua_tonumber(L, 2);
			Camera& cam = (Application::Get().layerGraphics)->GetGraphics()->GetCamera();
			cam.x = x;
			cam.y = y;
		}
		return 0;
	}

	static int GetCameraPos(lua_State* L)
	{
		// arguments - none
		int n = lua_gettop(L);
		if (n != 0)
		{
			lua_pushliteral(L, "incorect arguments - GetCameraPos");
			lua_error(L);
			return 0;
		}
		else
		{
			Camera& cam = (Application::Get().layerGraphics)->GetGraphics()->GetCamera();
			lua_pushnumber(L, cam.x );
			lua_pushnumber(L, cam.y );
			return 2;
		}
	}

	static int GetWindowDimensions(lua_State* L)
	{
		// arguments - none
		int n = lua_gettop(L);
		if (n != 0)
		{
			lua_pushliteral(L, "incorect arguments - GetWindowDimensions");
			lua_error(L);
			return 0;
		}
		else
		{
			int w = Application::Get().GetWindow().GetWidth();
			int h = Application::Get().GetWindow().GetHeight();
			lua_pushnumber(L, w);
			lua_pushnumber(L, h);
			return 2;
		}
	}


	void BindGraphicsEngineHooks(lua_State* L)
	{
		//Example
		//BindFunction(L, CallFunc, "Call_Function");               //arguments: string ScriptToFind, string Function, uint32_t Object

		BindFunction(L, DrawSprites, "draw_sprites");				//arguments: Sprite sprite
		BindFunction(L, SetTexture, "set_texture");				    //arguments: uid texture
		BindFunction(L, SetAnimationParams, "set_animation_params");//arguments: uid, animation rows, animation frames, cur row, speed
		BindFunction(L, GetCameraPos, "get_camera_pos");			//arguments: none, returns x, y
		BindFunction(L, SetCameraPos, "set_camera_pos");			//arguments: x, y
		BindFunction(L, GetWindowDimensions, "get_window_dimensions");	// arguments: none, returns width, height
	}
}