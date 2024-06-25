#pragma once

#include "DTWindow.h"
#include "Timer.h"

//TODO: Add docs
class DTApp
{
private: 
	DTWindow window;
	Timer timer;

	void RunFrame();

public:
	DTApp();
	int Run();
};

