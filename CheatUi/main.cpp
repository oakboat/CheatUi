#include "Cheat.h"
#include <memory>

int main(int, char**)
{
	std::unique_ptr<Cheat> cheat = std::make_unique<Cheat>();
	return cheat->Run();
}