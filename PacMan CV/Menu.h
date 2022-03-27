#pragma once
#include "io_utilities.h"
#include "Color.h"

class Menu
{
public:
	LEVEL GhostLevel();
	void ShowRules();
	bool StartScreenPrint(bool& NoColor);
};

