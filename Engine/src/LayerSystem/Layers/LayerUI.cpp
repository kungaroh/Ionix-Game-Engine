#include "LayerUI.h"
#include "Architecture/Application.h"

namespace IonixEngine
{
	void LayerUI::OnAttach() 
{
		m_UIManager = new UIManager();
		
	}



	void LayerUI::OnDetach() { }


	void LayerUI::OnLoaded()
	{
		m_UIManager->UIInit(Application::Get().GetWindow().GetSdlRenderer(), Application::Get().GetWindow().m_Window);
	}

	void LayerUI::OnUpdate() 
	{
		m_UIManager->UIUpdate(Application::Get().GetWindow().GetSdlRenderer(), Application::Get().GetWindow().m_Window);
	}

	void LayerUI::OnEvent(IonixEvent& e)
	{
		EventDispatcher dispatcher(e);
	}
}
