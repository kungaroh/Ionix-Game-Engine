#include "Architecture/Application.h"
#include "Components/SpriteComponent.h"
#include "Components/ScriptComponent.h"

namespace IonixEngine
{ 
	void InitHLTestGame()
	{
		// set up a test, create objects, attach components and so on

		Object* obj = Application::Get().layerObject->NewObject("test");
		//Object* obj = Application::Get().layerObject->GetScene()->GetObjectByUID(objUID);
		ScriptComponent* script = new ScriptComponent("movement");
		obj->AddComponent(script);

		SpriteComponent* sprite = new SpriteComponent();
		sprite->SetTexture("test_texture.png");
		sprite->SetWidth(50);
		sprite->SetHeight(50);
		obj->AddComponent(sprite);

		Application::Get().layerObject->GetScene()->AddObject(obj);
	}
}