#include "Architecture/Application.h"
#include "Components/SpriteComponent.h"
#include "Components/ScriptComponent.h"

namespace IonixEngine
{
	void InitTNTest()
	{ 
		uint32_t objUID = Application::Get().layerObject->NewObject();
		Object* obj = Application::Get().layerObject->GetScene()->GetObjectByUID(objUID);
		//ScriptComponent* script = new ScriptComponent("zIndexTesting");
		//obj->AddComponent(script);

		ScriptComponent* script2 = new ScriptComponent("movement");
		obj->AddComponent(script2);

		SpriteComponent* sprite = new SpriteComponent();
		//sprite->SetTexture("sdl2-spritesheet-actual2.png");
		sprite->SetTexture("test_texture.png");
		sprite->SetWidth(50);
		sprite->SetHeight(50);
		
		//sprite->Set
		sprite->SetZIndex(1);
		//sprite->SetxPos(20);
		//sprite->SetyPos(20);
		obj->AddComponent(sprite);
		
		obj->GetComponentOfType<TransformComponent>()->x = 100;
		obj->GetComponentOfType<TransformComponent>()->y = 100;
		Application::Get().layerObject->GetScene()->AddObject(obj);


		objUID = Application::Get().layerObject->NewObject();
		obj = Application::Get().layerObject->GetScene()->GetObjectByUID(objUID);
		sprite = new SpriteComponent();
		//sprite->SetTexture("sdl2-spritesheet-actual2.png");
		sprite->SetTexture("test_texture.png");
		sprite->SetWidth(100);
		sprite->SetHeight(100);

		//sprite->Set
		sprite->SetZIndex(0);
		//sprite->SetxPos(20);
		//sprite->SetyPos(20);
		obj->AddComponent(sprite);

		obj->GetComponentOfType<TransformComponent>()->x = 500;
		obj->GetComponentOfType<TransformComponent>()->y = 500;
		
		Application::Get().layerObject->GetScene()->AddObject(obj);
		

		objUID = Application::Get().layerObject->NewObject();
		obj = Application::Get().layerObject->GetScene()->GetObjectByUID(objUID);
		sprite = new SpriteComponent();
		//sprite->SetTexture("sdl2-spritesheet-actual2.png");
		sprite->SetTexture("test_texture.png");
		sprite->SetWidth(100);
		sprite->SetHeight(100);

		//sprite->Set
		sprite->SetZIndex(2);
		//sprite->SetxPos(20);
		//sprite->SetyPos(20);
		obj->AddComponent(sprite);

		obj->GetComponentOfType<TransformComponent>()->x = 200;
		obj->GetComponentOfType<TransformComponent>()->y = 300;
		Application::Get().layerObject->GetScene()->AddObject(obj);

#
		/*
		SpriteComponent* newSprite = new SpriteComponent();
		sprite->SetTexture("Rock.png");
		sprite->SetWidth(100);
		sprite->SetHeight(100);
		sprite->SetZIndex(1);
		obj->AddComponent(sprite);

		Application::Get().layerObject->GetScene()->AddObject(obj);
		*/
	/*
		uint32_t objUID = Application::Get().layerObject->NewObject();
		Object* obj = Application::Get().layerObject->GetScene()->GetObjectByUID(objUID);
		//ScriptComponent* script = new ScriptComponent("movement");
		//obj->AddComponent(script);

		SpriteComponent* sprite = new SpriteComponent();
		sprite->SetTexture("test_texture.png");
		sprite->SetWidth(50);
		sprite->SetHeight(50);
		sprite->SetZIndex(0);
		obj->AddComponent(sprite);

		Application::Get().layerObject->GetScene()->AddObject(obj);
	*/
	}




}