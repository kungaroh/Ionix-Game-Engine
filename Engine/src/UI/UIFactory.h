#pragma once
#include <SDL.h>
#include <imgui.h>
#include "UIStructures.h"
#include "UIGroup.h"

class UIFactory
{	
public:
	UIFactory() { }
	~UIFactory() {}

	static void DrawLabel(UIQueueData* uqd);
	static void DrawButton(UIQueueData* uqd);
};

