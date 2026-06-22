#include <iostream>
#include <thread>

void threadFunction(){

	std::cout << "Greettings \n";
}

int main(){

	std::thread t (threadFunction);

	std::cout << "Hello, World\n";

	t.join();
	return 0;
}
