#include <iostream>
#include "console3d.hpp"


int main(){
	Console3d cube{};
	cube.initConsoleWindow();
	cube.init();
	std::cout << "Hello, World\n";
	return 0;
}
