#pragma once
#include <EngineIncludes.h>

class Source
{
public: 
	Source() { }
	~Source() { }

	void foobar();
};

void Source::foobar()
{
	Console::GetEngineLogger().info("Scripting Project Link");
}
