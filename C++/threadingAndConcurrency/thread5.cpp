#include <iostream>
#include <thread>
#include <mutex>



std::mutex mtx{};

void process_data(int data){
	std::unique_lock<std::mutex> lck(mtx, std::defer_lock);

	lck.lock();
	std::cout << " Processing data: " << data << '\n';
	lck.unlock();
}


int main(){
	std::thread t1(process_data, 10);
	std::thread t2(process_data, 20);

	t1.join();
	t2.join();

	return 0;
}
