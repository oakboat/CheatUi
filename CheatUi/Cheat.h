#pragma once
#include <memory>
#include "Ui.h"

class Cheat
{
public:
	int Render();
	int Run();

	std::unique_ptr<Ui>	ui;
};

