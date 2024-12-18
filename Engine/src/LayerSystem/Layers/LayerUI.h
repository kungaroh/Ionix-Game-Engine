#pragma once
#include "UI/UIManager.h"
#include "LayerSystem/Layer.h"
#include "EventSystem/Event.h"


namespace IonixEngine
{
	class LayerUI : public Layer
	{
	public:
		LayerUI(int id) : Layer(id)
		{			
		}

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnLoaded() override;
		virtual void OnUpdate() override;
		virtual void OnEvent(IonixEvent& e) override;
		UIManager* GetUIManager() { return m_UIManager; }


	private:
		UIManager* m_UIManager;
	};
}


