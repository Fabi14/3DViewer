#pragma once
#include <string>

class DebugOutput
{
public:
	static void enable();

	static void printDebugMessage(const std::string& message);
};

