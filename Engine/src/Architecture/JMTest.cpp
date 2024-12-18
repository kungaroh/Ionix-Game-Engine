#include "Architecture/Application.h"
#include "Components/SpriteComponent.h"
#include "Components/ScriptComponent.h"
#include "Components/PhysicsComponent.h"

namespace IonixEngine
{ 
	void InitJMTest()
	{
		Object* newObject = new Object();
		newObject->SetGameObjectName("Player");

		PhysicsComponent* phys = new PhysicsComponent(16, 16, 1.0, 1.0, 1.0, false, false, false, false); // not trigger, kinematic
		newObject->AddComponent(phys);
		newObject->SetObjectPosition(100, 100);

		SpriteComponent* sprite = new SpriteComponent();
		sprite->SetTexture("test_texture.png");


		sprite->SetWidth(16);
		sprite->SetHeight(16);
		newObject->AddComponent(sprite);
	
		Application::Get().layerObject->GetScene()->AddObject(newObject);	
	}
}