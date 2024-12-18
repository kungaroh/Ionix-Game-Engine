#pragma once
#include <cinttypes>

// simple system for generating a unique identifier. 
// it's just an integer that gets incremented every time a new
// UID is asked for
class ObjectUID
{
	static uint32_t curUid;
public:
	static uint32_t UID() { return curUid++; }
};