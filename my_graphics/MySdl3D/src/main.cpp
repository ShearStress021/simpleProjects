#include <iostream>
#include "renderer.hpp"

int main(int argc, char* argv[])
{
	Renderer app{};
	if(app.init()){
		app.run();
	}
}


