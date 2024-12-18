#pragma once
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"

namespace IonixEngine
{
	class LayerPhysics : public Layer
	{
	public:
		LayerPhysics(int id) : Layer(id)
		{
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		void OnUpdate(float deltaTime);
		virtual void OnEvent(IonixEvent& e) override;
		Physics* GetPhysics();
		Scene* GetPhysScene();

		//Specialist function for physics
		//void UpdatePhysics();
		void OnCollision();
		void OnTriggerEnter();
		void OnCollisionExit();
		void OnTriggerExit();
		void RayCasting();
		Physics* GetPhysics() const { return m_physics; }
	private:
		Physics* m_physics;
	};
}