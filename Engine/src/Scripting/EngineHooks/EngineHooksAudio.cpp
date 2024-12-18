#include "EngineHooksAudio.h"
#include "Logging/Console.h"
#include "Scripting/Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include <string>
#include "Audio/Audio.h"
#include "LayerSystem/Layers/LayerAudio.h"
using namespace std;


namespace IonixEngine
{
	LayerAudio* layerAudio;

	int PlayAudio(lua_State* L)
	{
		//Needs if to check if audio chunk already loaded
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isstring(L, 1)) && !(lua_isnumber(L, 2)))
		{
			return luaL_error(L, "Incorrect arguments - expected a file location and a number of loops");
		}
		const char* fileLocation = lua_tostring(L, 1);
		int loops = lua_tointeger(L, 2);

		int handle = Application::Get().layerAudio->PlayAudio(fileLocation, loops);

		lua_pushinteger(L, handle);
		return 1;
	}

	int PauseAudio(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isinteger(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected int handle");
		}

		int handle = lua_tointeger(L, 1);

		Application::Get().layerAudio->PauseAudio(handle);

		return 0;
	}

	int ResumeAudio(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isinteger(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected int handle");
		}

		int handle = lua_tointeger(L, 1);

		Application::Get().layerAudio->ResumeAudio(handle);

		return 0;
	}

	int FadeIn(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isnumber(L, 1) && !(lua_isinteger(L, 2))))
		{
			return luaL_error(L, "Incorrect arguments - expected a time in ms, and int handle");
		}

		int ms = lua_tointeger(L, 1);
		const char* fileLocation = lua_tostring(L, 2);
		int loops = lua_tointeger(L, 3);

		Mix_Chunk* audioChunk = Application::Get().layerAudio->LoadWAV(fileLocation);

		Application::Get().layerAudio->FadeIn(ms, audioChunk, loops);

		return 0;
	}

	int FadeOut(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isnumber(L, 1) && !(lua_isinteger(L, 2))))
		{
			return luaL_error(L, "Incorrect arguments - expected a time in ms, and int handle");
		}

		int ms = lua_tointeger(L, 1);
		int handle = lua_tointeger(L, 2);

		Application::Get().layerAudio->FadeOut(ms, handle);

		return 0;
	}

	int SetVolume(lua_State* L)
	{
		int n = lua_gettop(L);
		/*if (n != 2 || !(lua_isnumber(L, 1) && !(lua_isinteger(L, 2))))
		{
			return luaL_error(L, "Incorrect arguments - expected volume, and int handle");
		}*/

		int volume = lua_tonumber(L, 1);
		int handle = lua_tointeger(L, 2);

		Application::Get().layerAudio->SetVolume(volume, handle);

		return 0;
	}

	int TimedPlay(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isinteger(L, 1)) && !(lua_isnumber(L, 2)))
		{
			return luaL_error(L, "Incorrect arguments - expected int handle and a interval");
		}
		int handle = lua_tointeger(L, 1);
		float interval = lua_tonumber(L, 2);

		Application::Get().layerAudio->TimedPlay(handle, interval);

		return 0;
	}

	int RandomTimedPlay(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isinteger(L, 1)) && !(lua_isnumber(L, 2)))
		{
			return luaL_error(L, "Incorrect arguments - expected int handle and min and max");
		}
		int handle = lua_tointeger(L, 1);
		float min = lua_tonumber(L, 2);
		float max = lua_tonumber(L, 3);

		Application::Get().layerAudio->RandomTimedPlay(handle, min, max);

		return 0;
	}

#
	int ClearChannel(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !(lua_isinteger(L, 1)))
		{
			return luaL_error(L, "Incorrect arguments - expected int handle");
		}

		int handle = lua_tointeger(L, 1);

		Application::Get().layerAudio->ClearChannel(handle);

		return 0;
	}
	

	int ClearAllChannels(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			return luaL_error(L, "Incorrect arguments - Unexpected Variable");
		}

		Application::Get().layerAudio->ClearAllChannels();

		return 0;
	}


	int PauseAllAudio(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 0)
		{
			return luaL_error(L, "Incorrect arguments - Unexpected Variable");
		}

		Application::Get().layerAudio->PauseAllAudio();

		return 0;
	}

	void BindAudioEngineHooks(lua_State* L) {
		BindFunction(L, PlayAudio, "play_audio");
		BindFunction(L, PauseAudio, "pause_audio");
		BindFunction(L, ResumeAudio, "resume_audio");
		BindFunction(L, SetVolume, "set_volume");
		BindFunction(L, FadeIn, "fade_in");
		BindFunction(L, FadeOut, "fade_out");
		BindFunction(L, TimedPlay, "timed_play");
		BindFunction(L, RandomTimedPlay, "random_timed_play");
		BindFunction(L, ClearChannel, "ClearChannel");
		BindFunction(L, ClearAllChannels, "ClearAllChannel");
		BindFunction(L, PauseAllAudio, "PauseAllAudio");
	}
}