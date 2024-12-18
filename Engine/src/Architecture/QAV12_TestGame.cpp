#include "Architecture/Application.h"
#include "Components/SpriteComponent.h"
#include "Components/ScriptComponent.h"
#include "Components/PhysicsComponent.h"
#include "ResourceManager.h"

namespace IonixEngine
{ 

	void InitRPG()
	{
		Object* obj;
		ScriptComponent* script;
		SpriteComponent* sprite;
		PhysicsComponent* phys;
		//---------------------------------------------------------------------------------------------
		// terrain tile prototypes

		// load texture tiles
		ResourceManager::GetInstance().CreateAndAddTiles("dungeons3.png",16);
		ResourceManager::GetInstance().CreateAndAddTiles("dungeons2.png",16);
		ResourceManager::GetInstance().CreateAndAddTiles("dungeons.png",16);

		obj = Application::Get().layerObject->NewObject("Tile1Proto");
		sprite = new SpriteComponent();
		sprite->SetTexture("dungeons3.png_tile_0");
		sprite->SetHeight(64);
		sprite->SetWidth(64);
		obj->AddComponent(sprite);
		Application::Get().layerObject->GetScene()->AddObject(obj);
		obj->SetObjectPosition(-5000.0f, -5000.0f);
		obj->SetObjectZLayer(2);

		obj = Application::Get().layerObject->NewObject("Tile2Proto");
		sprite = new SpriteComponent();
		sprite->SetTexture("dungeons2.png_tile_0");
		sprite->SetHeight(64);
		sprite->SetWidth(64);
		obj->AddComponent(sprite);

		phys = new PhysicsComponent(64, 64, 0.0, 0.0, 0.0, true, false, false, false); // trigger, kinematic
		obj->AddComponent(phys);

		Application::Get().layerObject->GetScene()->AddObject(obj);
		obj->SetObjectPosition(-5000.0f, -5000.0f);
		obj->SetObjectZLayer(2);

		//---------------------------------------------------------------------------------------------
		// player controller
		obj = Application::Get().layerObject->NewObject("Player");

		script = new ScriptComponent("hero");
		obj->AddComponent(script);

		sprite = new SpriteComponent();
		sprite->SetTexture("hero2.png");
		sprite->SetHeight(64);
		sprite->SetWidth(64);
		obj->AddComponent(sprite);

		// collider slightly smaller than 64 so player can squeeze through gaps
		phys = new PhysicsComponent(60, 60, 0.0, 0.0, 1.0, false, false, false, false); // trigger, kinematic
		obj->AddComponent(phys);

		obj->SetObjectPosition(600, 350);
		obj->SetTag("player");
		Application::Get().layerObject->GetScene()->AddObject(obj);
		phys->SetGravityScale(0.0f);
		phys->SetRotationActive(false);

		//---------------------------------------------------------------------------------------------
		// level builder
		obj = Application::Get().layerObject->NewObject("LevelGenerator");
		script = new ScriptComponent("level_generator");
		obj->AddComponent(script);
		Application::Get().layerObject->GetScene()->AddObject(obj);
		obj->SetObjectZLayer(0);


	}
	void InitSpaceShooter()
	{
		Object* obj;
		ScriptComponent* script;
		SpriteComponent* sprite;
		PhysicsComponent* phys;
		
		//---------------------------------------------------------------------------------------------
		// player controller
		obj = Application::Get().layerObject->NewObject("Player");
		
		script = new ScriptComponent("player");
		obj->AddComponent(script);
		
		sprite = new SpriteComponent();
		sprite->SetTexture("ship.png");
		sprite->SetHeight(64);
		sprite->SetWidth(64);
		obj->AddComponent(sprite);

		phys = new PhysicsComponent(64, 64, 0.0, 0.0, 0.0, false, true, true, false); // trigger, kinematic
		obj->AddComponent(phys);


		obj->SetObjectPosition(600, 650);
		obj->SetTag("player");
		Application::Get().layerObject->GetScene()->AddObject(obj);
		////---------------------------------------------------------------------------------------------

		//---------------------------------------------------------------------------------------------
		// bullet prefab
		obj = Application::Get().layerObject->NewObject("BulletPrefab");
		
		script = new ScriptComponent("bullet");
		obj->AddComponent(script);
		
		sprite = new SpriteComponent();
		sprite->SetTexture("red.png");
		sprite->SetHeight(16);
		sprite->SetWidth(4);
		obj->AddComponent(sprite);
		
		phys = new PhysicsComponent(4, 16, 0.0, 0.0, 0.0, false, true, true, false); // trigger, kinematic
		obj->AddComponent(phys);

		obj->SetObjectPosition(-100, 100); // off screen
		obj->SetTag("bullet");

		Application::Get().layerObject->GetScene()->AddObject(obj);

		////---------------------------------------------------------------------------------------------
		//// enemy prefab
		obj = Application::Get().layerObject->NewObject("EnemyPrefab");
		
		sprite = new SpriteComponent();
		sprite->SetTexture("enemy1.png");
		sprite->SetHeight(32);
		sprite->SetWidth(32);
		obj->AddComponent(sprite);

		script = new ScriptComponent("enemy");
		obj->AddComponent(script);

		phys = new PhysicsComponent(32, 32, 0.0, 0.0, 0.0, false, true, true, false); // trigger, kinematic
		obj->AddComponent(phys);
		
		obj->SetObjectPosition(-1000, 100); // off screen
		obj->SetTag("enemy");

		Application::Get().layerObject->GetScene()->AddObject(obj);

		//---------------------------------------------------------------------------------------------
		// enemy bullet prefab
		obj = Application::Get().layerObject->NewObject("EnemyBulletPrefab");
		
		sprite = new SpriteComponent();
		sprite->SetTexture("green.png");
		sprite->SetHeight(16);
		sprite->SetWidth(4);
		obj->AddComponent(sprite);
		
		phys = new PhysicsComponent(4, 16, 0.0, 0.0, 0.0, false, true, true, false); // trigger, kinematic
		obj->AddComponent(phys);
		
		script = new ScriptComponent("enemy_bullet");
		obj->AddComponent(script);

		obj->SetObjectPosition(-800, -800); // off scrren
		obj->SetTag("enemybullet");

		Application::Get().layerObject->GetScene()->AddObject(obj);
		
		//---------------------------------------------------------------------------------------------
		// game manager
		obj = Application::Get().layerObject->NewObject("GameManager");
		
		script = new ScriptComponent("game_manager");
		obj->AddComponent(script);

		Application::Get().layerObject->GetScene()->AddObject(obj);

		//---------------------------------------------------------------------------------------------
		// scrolling background 
		obj = Application::Get().layerObject->NewObject("Background1");

		sprite = new SpriteComponent();
		sprite->SetTexture("background.png");
		sprite->SetHeight(720);
		sprite->SetWidth(1280);
		obj->AddComponent(sprite);

		script = new ScriptComponent("background_scroller");
		obj->AddComponent(script);
	
		obj->SetObjectZLayer(2);
		obj->SetObjectPosition(640.0, 360.0f);
		Application::Get().layerObject->GetScene()->AddObject(obj);
		obj = Application::Get().layerObject->NewObject("Background2");

		sprite = new SpriteComponent();
		sprite->SetTexture("background.png");
		sprite->SetHeight(720);
		sprite->SetWidth(1280);
		obj->AddComponent(sprite);

		script = new ScriptComponent("background_scroller");
		obj->AddComponent(script);

		obj->SetObjectZLayer(2);
		obj->SetObjectPosition(640.0, -360.0f);
		Application::Get().layerObject->GetScene()->AddObject(obj);


		//------------------------------------------------------------------------------------------------
		// explosion
		obj = Application::Get().layerObject->NewObject("ExplosionPrefab");

		sprite = new SpriteComponent();
		sprite->SetTexture("explosion/1_0.png");
		sprite->SetHeight(256);
		sprite->SetWidth(256);
		obj->AddComponent(sprite);

		script = new ScriptComponent("explosion");
		obj->AddComponent(script);

		obj->SetObjectPosition(-800, -800); // off scrren

		Application::Get().layerObject->GetScene()->AddObject(obj);





		// old explosion prefab - Tyler N
		/*
		obj = Application::Get().layerObject->NewObject("ExplosionPrefab");
		sprite = new SpriteComponent();
		sprite->SetTexture("ExplosionSpriteSheet.png");
		sprite->SetAnimationFrames(10.0f);
		sprite->SetAnimationRows(2.0f);
		sprite->SetCurrentAnimationRow(1.0f);
		sprite->SetAnimationSpeed(0.09f);
		sprite->SetHeight(32);
		sprite->SetWidth(32);
		obj->AddComponent(sprite);

		script = new ScriptComponent("explosion");
		obj->AddComponent(script);

		phys = new PhysicsComponent(32, 32, 0.0, 0.0, 0.0, false, true, true);
		//obj->AddComponent(phys);

		obj->SetObjectPosition(-1000, 100);
		obj->SetTag("explosion");

		Application::Get().layerObject->GetScene()->AddObject(obj);
		*/
	}
}