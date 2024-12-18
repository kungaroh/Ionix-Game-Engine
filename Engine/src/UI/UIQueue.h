#pragma once
#include <SDL.h>
#include <imgui.h>
#include <string>
#include <vector>
#include <iostream>
#include <Logging/Console.h>
#include <unordered_map>
#include "UIStructures.h"
#include "UIFactory.h"
#include <cstring> // For strcpy and strlen

class UIQueue
{
public:
	UIQueue() {};
	~UIQueue() {};

    void AddLabel(const char* t, int x, int y, int givenID,int groupID = -1);
    void AddButton(const char* t, int posX, int posY, int sizeX, int sizeY, int givenID, int groupID = -1);
    void IterateList();

    void SetButtonPressed(int ID, bool pressed) {buttonPressedStates[ID] = pressed; std::cout << pressed;};
    bool GetButtonPressed(int ID) { return buttonPressedStates[ID]; };
    void ResetStates();

    void SetActiveUI(int ID, bool val)
    {
        UIQueueData* uqd = GetUIData(ID);
        uqd->enabled = val;
    }

    UIQueueData* GetUIData(int ID)
    {
        for (auto* uqd : uiElementslist)
        {
            if (uqd->uniqueID == ID)
            {
                return uqd;
            }
        }

        return nullptr;
    }

    void UpdateTextUI(int ID, const char* t)
    {
        UIQueueData* uqd = GetUIData(ID);

        if (uqd == nullptr) return;

        std::string newText(t);
        if (uqd->text == newText) return;

        uqd->text = newText;
    }

private:
    bool CheckIfIDExists(int ID);

    std::vector<UIQueueData*> uiElementslist;

    std::unordered_map< int, bool> buttonPressedStates;
};





