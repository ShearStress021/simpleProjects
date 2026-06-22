#include <iostream>
#include <thread>
#include <mutex>



std::mutex mtx;
int sharedData{};


void incrementSharedData(int n, const std::string_view& threadName){
	for(size_t i{}; i < n; ++i){
		mtx.lock();
		++sharedData;
		std::cout << threadName << " increments value to " << sharedData << '\n';
		mtx.unlock();
	}

}

int main(){
	std::thread t1(incrementSharedData, 5, "Thread 1");
	std::thread t2(incrementSharedData, 5, "Thread 2");


	t1.join();
	t2.join();

	return 0;
}
