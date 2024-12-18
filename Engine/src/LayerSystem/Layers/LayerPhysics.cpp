#pragma once
#include "EventSystem/Event.h"
#include "../src/Architecture/Application.h"
#include "LayerPhysics.h"
#include "LayerSystem/Layers/LayerPhysics.h"

namespace IonixEngine
{
	void LayerPhysics::OnAttach() 
	{
		m_physics = new Physics(0.0f, 10.0f);
	}

	void LayerPhysics::OnDetach() { }

	void LayerPhysics::OnLoaded()
	{
	}

	void LayerPhysics::OnUpdate(float deltaTime) 
	{
		m_physics->UpdatePhysics(deltaTime);
	}

	void LayerPhysics::OnEvent(IonixEvent& e)
	{
		EventDispatcher dispatcher(e);
	}

	Physics* LayerPhysics::GetPhysics() {
		return m_physics;
	}

	Scene* LayerPhysics::GetPhysScene() {
		return Application::Get().layerObject->GetScene();
	}

	//void LayerPhysics::UpdatePhysics() { }
	void LayerPhysics::OnCollision() { }
	void LayerPhysics::OnTriggerEnter() { }
	void LayerPhysics::OnCollisionExit() { }
	void LayerPhysics::OnTriggerExit() { }
	void LayerPhysics::RayCasting() { }
}