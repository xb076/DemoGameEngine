
#include <iostream>

namespace Engine {

	__declspec(dllimport) void Print();
}


int main(int argc, char* argv[])
{
	Engine::Print();

	std::cin.get();
	return 0;
}