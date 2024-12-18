#include "EngineHooksLibrary.h"
#include "Logging/Console.h"
#include "../Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

namespace IonixEngine
{

	// Variable classes

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Maths Library
	static int RoundToInt(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "not 1 number, please give one number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			int truncated = static_cast<int>(lua_tonumber(L, 1));

			if ((lua_tonumber(L, 1) - truncated) < 0.5) {
				lua_pushinteger(L, truncated);
			}
			else {
				lua_pushinteger(L, truncated + 1);
			}
			return 1;
		}
	}
	static int FloorToInt(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "not 1 number, please give one number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			lua_pushinteger(L,static_cast<int>(lua_tonumber(L, 1)));


			return 1;
		}
	}
	static int CeilToInt(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "not 1 number, please give one number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			int truncated = static_cast<int>(lua_tonumber(L, 1));

			if ((lua_tonumber(L, 1) - truncated) == 0) {
				lua_pushinteger(L, truncated);
			}
			else {
				lua_pushinteger(L, truncated + 1);
			}
			return 1;
		}
	}
	static int PowerOf(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !lua_isnumber(L, 1) && !lua_isnumber(L, 2))
		{
			lua_pushliteral(L, "not 2 numbers, please give two number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			lua_pushnumber(L, pow(lua_tonumber(L, 1),lua_tonumber(L, 2)));
			return 1;
		}
	}
	static int AbsValue(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "not 1 numbers, please give one number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			if (lua_tonumber(L, 1) >= 0) {
				lua_pushnumber(L, lua_tonumber(L, 1));
			}
			else {
				lua_pushnumber(L, -lua_tonumber(L, 1));

			}
			return 1;
		}
	}
	static int Rad2Deg(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "not 1 numbers, please give one number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{

			lua_pushnumber(L, lua_tonumber(L, 1) * ( 180/ M_PI ));

			return 1;
		}
	}
	static int Deg2Rad(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1 || !lua_isnumber(L, 1))
		{
			lua_pushliteral(L, "not 1 numbers, please give one number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			
		    lua_pushnumber(L, lua_tonumber(L, 1)*(M_PI /180));
			
			return 1;
		}
	}
	static int Clamp(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 3 || !lua_isnumber(L, 1)&&!lua_isnumber(L, 2)&& !lua_isnumber(L, 3))
		{
			lua_pushliteral(L, "not 3 numbers, please give 3 number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			if (lua_tonumber(L, 1) < lua_tonumber(L, 2)) {
				lua_pushnumber(L, lua_tonumber(L, 2));
			}
			else if(lua_tonumber(L, 1) > lua_tonumber(L, 3)){
				lua_pushnumber(L, lua_tonumber(L, 3));
			}
			else {
				lua_pushnumber(L, lua_tonumber(L, 1));
			}

			return 1;
		}
	}
	static int Normalize(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !lua_isnumber(L, 1) && !lua_isnumber(L, 2))
		{
			lua_pushliteral(L, "not 2 numbers, please give 2 number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			float div = sqrt(pow(lua_tonumber(L, 1),2)+ pow(lua_tonumber(L, 2), 2));
			lua_pushnumber(L, lua_tonumber(L, 1) / div);
			lua_pushnumber(L, lua_tonumber(L, 2) / div);
			return 2;
		}
	}
	static int Magnitude(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !lua_isnumber(L, 1) && !lua_isnumber(L, 2))
		{
			lua_pushliteral(L, "not 2 numbers, please give 2 number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{
			float mag = sqrt(pow(lua_tonumber(L, 1), 2) + pow(lua_tonumber(L, 2), 2));
			lua_pushnumber(L, mag);

			return 1;
		}
	}
	static int Interpolate(lua_State* L) {

		int n = lua_gettop(L);
		if (n == 3 || lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			lua_pushnumber(L, ((1 - lua_tonumber(L, 1)) * lua_tonumber(L, 2)) + (lua_tonumber(L, 1) * lua_tonumber(L, 3)));
			return 1;
		}
		else
		{

			lua_pushliteral(L, "not 3 numbers, please give 3 number, very disapointed");
			lua_error(L);
			return 0;
		}
	}

	static int BillenearInterpolate(lua_State* L) {

		int n = lua_gettop(L);//x,y,BL,BR,TL,TR
		if (n == 6 || lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3)&& lua_isnumber(L, 4) && lua_isnumber(L, 5) && lua_isnumber(L, 6))
		{
			float x = lua_tonumber(L, 1);
			float y = lua_tonumber(L, 2);
			float BL = lua_tonumber(L, 3);
			float BR = lua_tonumber(L, 4);
			float TL = lua_tonumber(L, 5);
			float TR = lua_tonumber(L, 6);

			lua_pushnumber(L, (1 - x) * (1 - y) * BL + x * (1 - y) * BR + ((1 - x) * y * TL) + (x * y * TR));
			return 1;
		}
		else
		{

			lua_pushliteral(L, "not 6 numbers, please give 6 number, :-( ");
			lua_error(L);
			return 0;
		}
	}

	int hash(int x, int y) {
		int seed = x * 374761393 + y * 668265263; // Some large prime numbers
		seed = (seed ^ (seed >> 13)) * 1274126177;
		return (seed ^ (seed >> 16)) & 0x7FFFFFFF;
	}

	//https://adrianb.io/2014/08/09/perlinnoise.html
	static int PerlinNoise(lua_State* L)
	{
		
		int n = lua_gettop(L);
		if (n == 3 || lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{
			float CellSize = lua_tonumber(L,3);
			float x = lua_tonumber(L, 1) / CellSize;
			float y = lua_tonumber(L, 2) / CellSize;
			int x1 = static_cast<int>(x);
			int y1 = static_cast<int>(y);

			// generate a height at each corner of cell
			float BL = static_cast<float>(hash(x1, y1)) / 0x7FFFFFFF;
			float BR = static_cast<float>(hash(x1 + 1, y1)) / 0x7FFFFFFF;
			float TL = static_cast<float>(hash(x1, y1 + 1)) / 0x7FFFFFFF;
			float TR = static_cast<float>(hash(x1 + 1, y1 + 1)) / 0x7FFFFFFF;

			x = x - x1;
			y = y - y1;

			
			float height = (1 - x) * (1 - y) * BL + x * (1 - y) * BR + ((1 - x) * y * TL) + (x * y * TR);
			lua_pushnumber(L, height);
	
			return 1;
		}
		if (n == 2 || lua_isnumber(L, 1) && lua_isnumber(L, 2))
		{
			float CellSize = 5;
			float x = lua_tonumber(L, 1) / CellSize;
			float y = lua_tonumber(L, 2) / CellSize;
			int x1 = static_cast<int>(x);
			int y1 = static_cast<int>(y);

			// generate a height at each corner of cell
			float BL = static_cast<float>(hash(x1, y1)) / 0x7FFFFFFF;
			float BR = static_cast<float>(hash(x1 + 1, y1)) / 0x7FFFFFFF;
			float TL = static_cast<float>(hash(x1, y1 + 1)) / 0x7FFFFFFF;
			float TR = static_cast<float>(hash(x1 + 1, y1 + 1)) / 0x7FFFFFFF;

			x = x - x1;
			y = y - y1;


			float height = (1 - x) * (1 - y) * BL + x * (1 - y) * BR + ((1 - x) * y * TL) + (x * y * TR);
			lua_pushnumber(L, height);

			return 1;
		}
		else
		{
	
			lua_pushliteral(L, "not 2 or 3 numbers, please give 2 or 3 number, very disapointed");
			lua_error(L);
			return 0;
		}
	}

	

	static int RandomRangeFloat(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 2 || lua_isnumber(L, 1) && lua_isnumber(L, 2))
		{
			// Get a different random number each time the program runs
			srand(static_cast<unsigned>(time(0)));

			double min = lua_tonumber(L, 1);
			double max = lua_tonumber(L, 2);
			
			double randomNum = min + (static_cast<double>(rand()) / RAND_MAX) * (max - min);

			lua_pushnumber(L, randomNum);
			return 1;
		}
		else if (n == 3 || lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{

			srand(lua_tonumber(L, 3));

			double min = lua_tonumber(L, 1);
			double max = lua_tonumber(L, 2);

			double randomNum = min + (static_cast<double>(rand()) / RAND_MAX) * (max - min);

			lua_pushnumber(L, randomNum);
			return 1;
		}
		else {
			lua_pushliteral(L, "not a valid input, i expected more from you");
			return 0;
		}
	}
	static int RandomRangeInt(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 2 || lua_isnumber(L, 1) && lua_isnumber(L, 2))
		{
			// Get a different random number each time the program runs
			srand(static_cast<unsigned>(time(0)));

			int upperBound = static_cast<int>(lua_tonumber(L, 2))- static_cast<int>(lua_tonumber(L, 1));
			int randomNum = rand() % upperBound;

			randomNum += static_cast<int>(lua_tonumber(L, 1));
			lua_pushnumber(L, randomNum);
			return 1;
		}
		else if (n == 3 || lua_isnumber(L, 1) && lua_isnumber(L, 2) && lua_isnumber(L, 3))
		{

			srand(lua_tonumber(L, 3));

			int upperBound = static_cast<int>(lua_tonumber(L, 2))- static_cast<int>(lua_tonumber(L, 1));
			int randomNum = rand() % upperBound;

			randomNum += static_cast<int>(lua_tonumber(L, 1));
			lua_pushnumber(L, randomNum);
			return 1;
		}
		else {
			lua_pushliteral(L, "not a valid input, i expected more from you");
			return 0;
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	class luaVector2 {
	public:
		float x, y;

		luaVector2(float x = 0, float y = 0) : x(x), y(y) {}

		float magnitude() const {
			return sqrt(x * x + y * y);
		}

	};



	// variable functions

	// Vector2




	static int newVector2(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2 || !lua_isnumber(L, 1)&& !lua_isnumber(L, 2))
		{
			lua_pushliteral(L, "not 2 numbers, please give 2 number, very disapointed");
			lua_error(L);
			return 0;
		}
		else
		{

			
			float x = (float)luaL_checknumber(L, 1);
			float y = (float)luaL_checknumber(L, 2);

			
			

			
			luaVector2* vec = (luaVector2*)lua_newuserdata(L, sizeof(luaVector2));
			*vec = luaVector2(x, y);

			
			luaL_getmetatable(L, "Vector2MetaTable");
			lua_setmetatable(L, -2);

			return 1; 
		}

	}

	////////////////////////////////////////////////////////////////////////////////////////////////
	// setters and getters
	int Vector2_set(lua_State* L) {
		luaVector2* vec = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");

		
			const char* field = luaL_checkstring(L, 2);
			float value = (float)luaL_checknumber(L, 3);

			if (strcmp(field, "x") == 0) {
				vec->x = value;  // Set vec.x
			}
			else if (strcmp(field, "y") == 0) {
				vec->y = value;  // Set vec.y
			}
			else {
				luaL_error(L, "Invalid field: %s", field);
			}
		
		
		return 0;
	}
	int Vector2_Reassign(lua_State* L) {

		luaVector2* vec = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");

		float xvalue = (float)luaL_checknumber(L, 2);
		float yvalue = (float)luaL_checknumber(L, 3);
		vec->x = xvalue;
		vec->y = yvalue;

		lua_pushvalue(L, 1);
		return 1;
	}
	int Vector2_get(lua_State* L) {
		luaVector2* vec = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");
		const char* field = luaL_checkstring(L, 2);

		if (strcmp(field, "x") == 0) {
			lua_pushnumber(L, vec->x);
		}
		else if (strcmp(field, "y") == 0) {
			lua_pushnumber(L, vec->y);
		}
		else if (strcmp(field, "magnitude") == 0) {
			lua_pushnumber(L, vec->magnitude());
		}
		else if (strcmp(field, "normalize") == 0) {
			vec->x /= vec->magnitude();
			vec->y /= vec->magnitude();
			lua_pushvalue(L, 1);
		}
		else {
			// Attempt to get methods from the metatable
			luaL_getmetatable(L, "Vector2MetaTable");
			lua_pushstring(L, field);
			lua_rawget(L, -2);
			if (!lua_isnil(L, -1)) {
				return 1; // Return the method
			}
			luaL_error(L, "Invalid field: %s", field);
		}
		return 1;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////
	// Vec2 Math Functions

	int Vector2_add(lua_State* L) {
		luaVector2* vec1 = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");
		luaVector2* vec2 = (luaVector2*)luaL_checkudata(L, 2, "Vector2MetaTable");

		vec1->x += vec2->x;
		vec1->y += vec2->y;

		lua_pushvalue(L, 1); // Return the modified vec1
		return 1;
	}
	int Vector2_Subtract(lua_State* L) {
		luaVector2* vec1 = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");
		luaVector2* vec2 = (luaVector2*)luaL_checkudata(L, 2, "Vector2MetaTable");

		vec1->x -= vec2->x;
		vec1->y -= vec2->y;

		lua_pushvalue(L, 1); // Return the modified vec1
		return 1;
	}

	int Vector2_Multiply(lua_State* L) {
		luaVector2* vec1 = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");
		if (lua_isnumber(L, 2)) {
			float val = lua_tonumber(L, 2);

			vec1->x *= val;
			vec1->y *= val;

			lua_pushvalue(L, 1); // Return the modified vec1
			return 1;
		}
		else {
			luaVector2* vec2 = (luaVector2*)luaL_checkudata(L, 2, "Vector2MetaTable");

			vec1->x *= vec2->x;
			vec1->y *= vec2->y;

			lua_pushvalue(L, 1); // Return the modified vec1
			return 1;
		}
	}
	
	int Vector2_Divide(lua_State* L) {
		luaVector2* vec1 = (luaVector2*)luaL_checkudata(L, 1, "Vector2MetaTable");
		if (lua_isnumber(L, 2)) {
			float val = lua_tonumber(L, 2);

			vec1->x /= val;
			vec1->y /= val;

			lua_pushvalue(L, 1); // Return the modified vec1
			return 1;
		}
		else {
			luaVector2* vec2 = (luaVector2*)luaL_checkudata(L, 2, "Vector2MetaTable");

			vec1->x /= vec2->x;
			vec1->y /= vec2->y;

			lua_pushvalue(L, 1); // Return the modified vec1
			return 1;
		}
	}

	void registerVector2(lua_State* L) {

		luaL_newmetatable(L, "Vector2MetaTable");

		lua_pushstring(L, "__index");
		lua_pushcfunction(L, Vector2_get);
		lua_settable(L, -3);

		lua_pushstring(L, "__newindex");
		lua_pushcfunction(L, Vector2_set);
		lua_settable(L, -3);

		lua_pushstring(L, "Set");
		lua_pushcfunction(L, Vector2_Reassign);
		lua_settable(L, -3);

		// Add method binding
		lua_pushstring(L, "add");
		lua_pushcfunction(L, Vector2_add);
		lua_settable(L, -3);

		lua_pushstring(L, "Sub");
		lua_pushcfunction(L, Vector2_Subtract);
		lua_settable(L, -3);

		lua_pushstring(L, "Mult");
		lua_pushcfunction(L, Vector2_Multiply);
		lua_settable(L, -3);

		lua_pushstring(L, "Div");
		lua_pushcfunction(L, Vector2_Divide);
		lua_settable(L, -3);

		lua_pop(L, 1);
	}
	//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	void BindLibraryEngineHooks(lua_State* L) {
		// Maths
		BindFunction(L, RoundToInt, "RoundToInt");
		BindFunction(L, FloorToInt, "FloorToInt");
		BindFunction(L, CeilToInt, "CeilToInt");
		BindFunction(L, PowerOf, "PowerOf");
		BindFunction(L, AbsValue, "AbsValue");
		BindFunction(L, Rad2Deg, "Rad2Deg");
		BindFunction(L, Deg2Rad, "Deg2Rad");
		BindFunction(L, Clamp, "Clamp");
		BindFunction(L, Normalize, "Normalize");
		BindFunction(L, Magnitude, "Magnitude");
		BindFunction(L, RandomRangeInt, "RandomRangeInt");
		BindFunction(L, RandomRangeFloat, "RandomRangeFloat");
		BindFunction(L, PerlinNoise, "PerlinNoise");
		BindFunction(L, Interpolate, "Interpolate");
		BindFunction(L, BillenearInterpolate, "BillenearInterpolate");


		// Variable Meta Tables
		registerVector2(L);
		lua_register(L, "newVector2", newVector2);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}