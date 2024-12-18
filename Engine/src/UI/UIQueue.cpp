#include "UIQueue.h"
#include "Architecture/Application.h"

//function to call to add label to ui elements list
void UIQueue::AddLabel(const char* t, int x, int y, int uniqueID,int groupID)
{
	if (CheckIfIDExists(uniqueID))
	{
		Console::warning("The unique UI ID: " + std::to_string(uniqueID) + " is already in use.");
		return;
	}

	if (groupID != -1)
		IonixEngine::Application::Get().layerUI->GetUIManager()->uiGroup->CreateGroup(groupID);
	
	UIQueueData* uqd = new UIQueueData(label, t, ImVec2(x, y), uniqueID, groupID);
	uiElementslist.push_back(uqd);
}

//function to call to add button to ui elements list
void UIQueue::AddButton(const char* t, int posX, int posY, int sizeX, int sizeY, int uniqueID, int groupID)
{
	if (CheckIfIDExists(uniqueID))
	{
		Console::warning("The unique UI ID: " + std::to_string(uniqueID) + " is already in use.");
		return;
	}

	if (groupID != -1)
		IonixEngine::Application::Get().layerUI->GetUIManager()->uiGroup->CreateGroup(groupID);

	UIQueueData* uqd = new UIQueueData(button, t, ImVec2(posX, posY), ImVec2(sizeX, sizeY), uniqueID, groupID);
	uiElementslist.push_back(uqd);
}

void UIQueue::IterateList()
{
	for (const auto& element : uiElementslist)
	{
		switch (element->elementType)
		{
		case button:
			UIFactory::DrawButton(element);		
			break;

		case label:
			UIFactory::DrawLabel(element);
			break;
		}
	}	
}

void UIQueue::ResetStates()
{
	for (int i = 0; i < buttonPressedStates.size(); i++)
	{
		if(GetButtonPressed(i) == true)
			SetButtonPressed(i, false);
	}
}

bool UIQueue::CheckIfIDExists(int id)
{
	for (auto* uqd : uiElementslist)
	{
		if (uqd->uniqueID == id)		
			return true;		
	}
	return false;
}