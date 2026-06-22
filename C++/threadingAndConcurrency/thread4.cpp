#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>




std::mutex mtx{};


void printEven(int x){
	std::lock_guard<std::mutex> lock(mtx);
	if(x % 2 == 0) std::cout << x << " Is even\n";
	else std::cout << x <<  " Is odd\n";
}

void printEvenT(int i){
		if(i % 2 == 0) std::cout << i << " is even\n ";
		else std::cout << i << " is odd\n";
}

int main(){
	std::thread threads[100];

	auto start = std::chrono::steady_clock::now();
	for(size_t i{}; i < 100; ++i){
		threads[i] = std::thread(printEven, i);
	}

	for(auto& th: threads){
		th.join();
	}
	auto end = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> elapsed = end - start;

	std::cout << "Thread took " << elapsed.count() << '\n';
	
	auto begin = std::chrono::steady_clock::now();

	for(size_t i{}; i < 100; i++){
		printEvenT(i);
	}
	auto endd = std::chrono::steady_clock::now();

	std::chrono::duration<double, std::milli> elapsedT = endd - begin;

	std::cout << "No Thread took " << elapsedT.count() << '\n';
	



	return 0;
}


