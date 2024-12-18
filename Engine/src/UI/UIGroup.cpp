#include "UIGroup.h"

void UIGroup::GroupTest()
{
	// Declare a struct of type Group and use the constructor to set the values
	std::vector<UIQueueData> elementGroup;
	Group* exampleGroup = new Group(1, ImVec2(10, 10), elementGroup);
	//AddToGroupList(exampleGroup, 0);
	groupList.push_back(exampleGroup);
}

Group* UIGroup::GetGroup(int ID)
{
	for (const auto& group : groupList)
	{
		if (ID == group->groupID)
		{
			return group;
		}
	}
	return nullptr;
}

void UIGroup::CreateGroup(int ID)
{
	Group* newGroup = new Group(ID);
	groupList.push_back(newGroup);
}

void UIGroup::setGroupPosition(int ID, int x, int y)
{
	ImVec2 newPos = ImVec2(x, y);

	GetGroup(ID)->pos = newPos;
}
