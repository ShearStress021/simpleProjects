#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


std::mutex mtx{};
std::condition_variable cv{};
bool ready {false};


void printId(int id){
	std::unique_lock<std::mutex> lck{mtx};
	while(!ready) cv.wait(lck);
	std::cout << "Thread " << id << " is running\n";

}

void setReady(){
	std::lock_guard<std::mutex> lck{mtx};
	ready = true;
	cv.notify_all();
}



int main(){

	std::thread threads[10];

	for(size_t i{}; i < 10; i++){
		threads[i] = std::thread(printId, i + 1);
	}
	setReady();


	for(auto& th: threads){
		th.join();
	}

	return 0;
}
