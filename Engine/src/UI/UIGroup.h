#pragma once
#include <SDL.h>
#include <imgui.h>
#include <UI/UIFactory.h>
#include "UIStructures.h"

class UIGroup
{
    class UIQueue;

public:
    
    //void AddToGroupList(Group* group, int index) { groupList.push_back(group); } //insert(groupList.begin() + index, group)
    void GroupTest();

    Group* GetGroup(int ID);

    void CreateGroup(int ID);

    void setGroupPosition(int groupID, int x, int y);

private:

    std::vector<Group*> groupList;
};
