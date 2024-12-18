#include "EngineHooksPhysics.h"
#include "Logging/Console.h"
#include "../Scripting.h"
#include "Architecture/Application.h"
#include "EngineHooks.h"
#include <string>
#include "LayerSystem/Layers/LayerPhysics.h"
#include "Components/PhysicsComponent.h"
#include "Physics/Raycasting.h"
using namespace std;

namespace IonixEngine 
{	
	static int SetGravityScale(lua_State* L)
		//UID for object, graveScale
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2))))
		{
			return luaL_error(L, "Incorrect arguments - expects uid and graveScale number");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float graveScale = (float)lua_tonumber(L, 2);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();

				if (pc != nullptr)
				{
					pc->SetGravityScale(graveScale);
				}
			}
		}
		return 0;
	}

	static int AddForce(lua_State* L)
		//UID, force X, forrce Y, forcePosx, forcePosY
	{
		int n = lua_gettop(L);
		if (n != 5 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isnumber(L, 5)))))))
		{
			return luaL_error(L, "Incorrect arguments - expected UID, force X, forrce Y, forcePosx, forcePosY");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float forceX = (float)lua_tonumber(L, 2);
			float forceY = (float)lua_tonumber(L, 3);
			float forcePosX = (float)lua_tonumber(L, 4);
			float forcePosY = (float)lua_tonumber(L, 5);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();

				if (pc != nullptr)
				{
					pc->AddForce(forceX, forceY, forcePosX, forcePosY);
				}
			}
		}
		return 0;
	}

	static int AddBoxCollider(lua_State* L)
		//UID, posX, posY, w, h, isTrigger
	{
		int n = lua_gettop(L);
		if (n != 6 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isnumber(L, 5) && (lua_isboolean(L, 6))))))))
		{
			return luaL_error(L, "Incorrect arguments - expected UID, posX, posY, w, h, isTrigger");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float posX = (float)lua_tonumber(L, 2);
			float posY = (float)lua_tonumber(L, 3);
			float w = (float)lua_tonumber(L, 4);
			float h = (float)lua_tonumber(L, 5);
			bool isTrigger = (bool)lua_toboolean(L, 6);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();

				if (pc != nullptr)
				{
					pc->AddBoxCollider(posX, posY, w, h, isTrigger);
				}
			}
		}
		return 0;
	}

	static int AddCircleCollider(lua_State* L)
		//UID, posX, posY, radius, isTrigger
	{
		int n = lua_gettop(L);
		if (n != 5 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isboolean(L, 5)))))))
		{
			return luaL_error(L, "Incorrect arguments - expected UID, posX, posY, radius, isTrigger");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float posX = (float)lua_tonumber(L, 2);
			float posY = (float)lua_tonumber(L, 3);
			float radius = (float)lua_tonumber(L, 4);
			bool isTrigger = (bool)lua_toboolean(L, 5);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();

				if (pc != nullptr)
				{
					pc->AddCircleCollider(posX, posY, radius, isTrigger);
				}
			}
		}
		return 0;
	}

	static int RemoveCollider(lua_State* L)
		//UID, ID
	{
		int n = lua_gettop(L);
		if (n != 2 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2))))
		{
			return luaL_error(L, "Incorrect arguments - expected UID, collider ID");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float ID = (float)lua_tonumber(L, 2);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();

				if (pc != nullptr)
				{
					pc->RemoveCollider(ID);
				}
			}
		}
	}




	//Raycast functions Starts here

	static int Raycast(lua_State* L)
		//UID, ID
	{
		int n = lua_gettop(L);
		if (n != 6 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isnumber(L, 5) && (lua_isnumber(L, 6))))))))
		{
			return luaL_error(L, "Incorrect arguments - expected int startX, int startY, int dirX, int dirY, float length");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			int startX = lua_tonumber(L, 2);
			int startY = lua_tonumber(L, 3);
			int dirX = lua_tonumber(L, 4);
			int dirY = lua_tonumber(L, 5);
			float length = lua_tonumber(L, 6);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				Raycasting* ray = Application::Get().layerPhysics->GetPhysics()->getRaycast();
				
				if (ray != nullptr)
				{
					bool rayHit = ray->Raycast(startX, startY, dirX, dirY, length);
					lua_pushboolean(L, rayHit);
				}
			}

			return 1;
		}
	}

	static int RaycastHit(lua_State* L)
		//UID, ID
	{
		int n = lua_gettop(L);
		if (n != 6 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isnumber(L, 5) && (lua_isnumber(L, 6))))))))
		{
			return luaL_error(L, "Incorrect arguments - expected int startX, int startY, int dirX, int dirY, float length");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			int startX = lua_tonumber(L, 2);
			int startY = lua_tonumber(L, 3);
			int dirX = lua_tonumber(L, 3);
			int dirY = lua_tonumber(L, 4);
			float length = lua_tonumber(L, 5);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			std::vector<int> rayhits;

			if (o != nullptr)
			{
				Raycasting* ray = Application::Get().layerPhysics->GetPhysics()->getRaycast();

				if (ray != nullptr)
				{
					rayhits = ray->RaycastHit(startX, startY, dirX, dirY, length);
				}
			}
			for each (auto rayhit in rayhits)
			{
				lua_pushnumber(L, rayhit);
			}

			return rayhits.size();
		}
	}

	static int FirstRaycastHit(lua_State* L)
		//UID, ID
	{
		int n = lua_gettop(L);
		if (n != 6 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isnumber(L, 5) && (lua_isnumber(L, 6))))))))
		{
			return luaL_error(L, "Incorrect arguments - expected int startX, int startY, int dirX, int dirY, float length");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			int startX = lua_tonumber(L, 2);
			int startY = lua_tonumber(L, 3);
			int dirX = lua_tonumber(L, 3);
			int dirY = lua_tonumber(L, 4);
			float length = lua_tonumber(L, 5);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				Raycasting* ray = Application::Get().layerPhysics->GetPhysics()->getRaycast();

				if (ray != nullptr)
				{
					lua_pushnumber(L, ray->FirstRaycastHit(startX, startY, dirX, dirY, length));
				}
			}

			return 1;
		}
	}

	static int BoxCast(lua_State* L)
		//UID, ID
	{
		int n = lua_gettop(L);
		if (n != 6 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3) && (lua_isnumber(L, 4) && (lua_isnumber(L, 5) && (lua_isnumber(L, 6))))))))
		{
			return luaL_error(L, "Incorrect arguments - expected int startX, int startY, int dirX, int dirY, float length");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			int x = lua_tonumber(L, 2);
			int y = lua_tonumber(L, 3);
			int x2 = lua_tonumber(L, 4);
			int y2 = lua_tonumber(L, 5);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				Raycasting* ray = Application::Get().layerPhysics->GetPhysics()->getRaycast();

				if (ray != nullptr)
				{
					ray->BoxCast( x,  y,  x2,  y2);
				}
			}
		}
	}

	//velocity hooks
	static int SetVelocity(lua_State* L)
		//UID, vel X, vel Y
	{
		int n = lua_gettop(L);
		if (n != 3 || !(lua_isnumber(L, 1) && (lua_isnumber(L, 2) && (lua_isnumber(L, 3)))))
		{
			return luaL_error(L, "Incorrect arguments - expected UID, vel X, vel Y");
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			float velX = (float)lua_tonumber(L, 2);
			float velY = (float)lua_tonumber(L, 3);

			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);

			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();

				if (pc != nullptr)
				{
					pc->SetVelocity(velX, velY);
				}
			}
		}
		return 0;
	}

	static int GetVelocity(lua_State* L)
	{
		// UID, vel X, vel Y
		int n = lua_gettop(L);
		float velX = 0;
		float velY = 0;
		if (n != 1 || !(lua_isnumber(L, 1)))
		{
			lua_pushliteral(L, "Incorrect arguments - expected UID");
			lua_error(L);
		}
		else
		{
			uint32_t uid = (uint32_t)lua_tonumber(L, 1);
			// fill in x and y here from the engine
			Object* o = Application::Get().layerObject->GetScene()->GetObjectByUID(uid);
			if (o != nullptr)
			{
				PhysicsComponent* pc = o->GetComponentOfType<PhysicsComponent>();
				if (pc != nullptr)
				{
					pc->GetVelocity(velX, velY);
				}
			}
		}
		// put the two return values on the stack
		lua_pushnumber(L, velX);
		lua_pushnumber(L, velY);
		return 2;
	}

	void BindPhysicsEngineHooks(lua_State* L)
	{
		BindFunction(L, SetGravityScale, "set_gravity_scale");
		BindFunction(L, AddForce, "add_force");
		BindFunction(L, AddBoxCollider, "add_box_collider");
		BindFunction(L, AddCircleCollider, "add_circle_collider");
		BindFunction(L, RemoveCollider, "remove_collider");
		//raycasting hooks
		BindFunction(L, Raycast, "raycast");
		BindFunction(L, RaycastHit, "raycast_hit");
		BindFunction(L, BoxCast, "box_cast");
		//velocity hooks
		BindFunction(L, SetVelocity, "set_velocity");
		BindFunction(L, GetVelocity, "get_velocity");
	}
}