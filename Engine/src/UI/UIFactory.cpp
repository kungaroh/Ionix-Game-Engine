#include "UIFactory.h"
#include <Architecture/Application.h>

void UIFactory::DrawLabel(UIQueueData* uqd)
{
	if (!uqd->enabled) return;

	if (uqd->groupID != -1)
	{
		Group* fetchedGroup = IonixEngine::Application::Get().layerUI->GetUIManager()->uiGroup->GetGroup(uqd->groupID);
		ImVec2 newPos(uqd->pos.x + fetchedGroup->pos.x, uqd->pos.y + fetchedGroup->pos.y);

		ImGui::SetCursorPos(newPos);
		ImGui::Text(uqd->text.c_str());

		return;
	}
	else 
	{
		ImGui::SetCursorPos(uqd->pos);
		ImGui::Text(uqd->text.c_str());
	}
}

void UIFactory::DrawButton(UIQueueData* uqd)
{
	if (!uqd->enabled) return;

	if (uqd->groupID != -1)
	{
		Group* fetchedGroup = IonixEngine::Application::Get().layerUI->GetUIManager()->uiGroup->GetGroup(uqd->groupID);
		ImVec2 newPos(uqd->pos.x + fetchedGroup->pos.x, uqd->pos.y + fetchedGroup->pos.y);

		ImGui::SetCursorPos(newPos);

		if (ImGui::Button(uqd->text.c_str(), uqd->size))
		{
			IonixEngine::Application::Get().layerUI->GetUIManager()->uiQueue->SetButtonPressed(uqd->uniqueID, true);
		}

		return;
	}
	else
	{
		ImGui::SetCursorPos(uqd->pos);

		if (ImGui::Button(uqd->text.c_str(), uqd->size))
		{
			IonixEngine::Application::Get().layerUI->GetUIManager()->uiQueue->SetButtonPressed(uqd->uniqueID, true);
		}
	}
}
