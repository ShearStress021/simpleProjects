#include <iostream>
#include <thread>
#include <chrono>

void independentTread(){
	std::cout << "Start detach thread\n";
	std::this_thread::sleep_for(std::chrono::seconds(2));
	std::cout << "Exit detach thread\n";
}


int main(){

	std::thread t(independentTread);

	t.detach();

	std::cout << "Main thread\n";

	std::this_thread::sleep_for(std::chrono::seconds(1));
	return 0;
}
