
#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <string>


bool isPalindrome1(int x) {

	std::string s = std::to_string(x);
	int n = s.size();

	int l{0};
	int r{n - 1};


	while (l < r){
		if(s[l] != s[r]){
			return false;
		}

		l++;
		r--;
	}


	return true;
}

bool isPalindrome2(int x) {

	if (x < 0) return false;

	int res{0};


	while(x > res){
		res = (res * 10) + (x % 10);
		x/=10;
	}


	return (res == x || res/10 == x);
}






int main(){

	int target = 100;

	std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());

	bool res = isPalindrome1(target);


    std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());

	std::cout <<  "solution one " << std::chrono::duration_cast<std::chrono::duration<double>>(
                    _end - _start).count() << '\n';



	std::chrono::steady_clock::time_point _start1(std::chrono::steady_clock::now());

	bool res1 = isPalindrome2(target);

    std::chrono::steady_clock::time_point _end1(std::chrono::steady_clock::now());

	std::cout <<  "solution one " << std::chrono::duration_cast<std::chrono::duration<double>>(
                    _end1 - _start1).count() << '\n';


	std::chrono::steady_clock::time_point _start3(std::chrono::steady_clock::now());


    std::chrono::steady_clock::time_point _end3(std::chrono::steady_clock::now());

	std::cout <<  "solution one " << std::chrono::duration_cast<std::chrono::duration<double>>(
                    _end3 - _start3).count() << '\n';



	return 0;
}
