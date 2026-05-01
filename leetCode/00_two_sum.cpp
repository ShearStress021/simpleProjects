
#include <iostream>
#include <vector>
#include <chrono>
#include <unordered_map>
#include <string>


std::vector<int> twoSumSol1(std::vector<int>& nums, int target) {
	
	for (int i = 0; i < nums.size(); i++) {
		for (int j = i + 1; j < nums.size(); j++){
			int tot = nums[i] + nums[j];

			if (tot == target){
				return {i,j};
			}
		}
	}

	return {};

}

std::vector<int> twoSumSol2(std::vector<int>& nums, int target){

	std::unordered_map<int, int> numMap{};

	int n = nums.size();

	for (int i = 0; i < n; i++){
		numMap[nums[i]] = i;
	}


	for (int i = 0; i < n; i ++){
		int complement = target - nums[i];
		if(numMap.count(complement) && numMap[complement] != 1){
			return {i, numMap[complement]};
		}
	}

	return {};
}

std::vector<int> twoSumSol3(std::vector<int>& nums, int target){
	std::unordered_map<int, int> numMap{};

	int n = nums.size();


	for (int i = 0; i < n; i++){
		int complement = target - nums[i];


		if (numMap.count(complement)){
			return {numMap[complement], i};
		}

		numMap[nums[i]] = i;
	}


	return {};


}


int main(){

	int target = 9;
	std::vector<int> nums {2,7,11,15};

	std::chrono::steady_clock::time_point _start(std::chrono::steady_clock::now());

	auto res1 = twoSumSol1(nums, target);

    std::chrono::steady_clock::time_point _end(std::chrono::steady_clock::now());

	std::cout <<  "solution one " << std::chrono::duration_cast<std::chrono::duration<double>>(
                    _end - _start).count() << '\n';



	std::chrono::steady_clock::time_point _start1(std::chrono::steady_clock::now());

	auto res2 = twoSumSol2(nums, target);

    std::chrono::steady_clock::time_point _end1(std::chrono::steady_clock::now());

	std::cout <<  "solution one " << std::chrono::duration_cast<std::chrono::duration<double>>(
                    _end1 - _start1).count() << '\n';


	std::chrono::steady_clock::time_point _start3(std::chrono::steady_clock::now());

	auto res3 = twoSumSol3(nums, target);

    std::chrono::steady_clock::time_point _end3(std::chrono::steady_clock::now());

	std::cout <<  "solution one " << std::chrono::duration_cast<std::chrono::duration<double>>(
                    _end3 - _start3).count() << '\n';

	for (int j = 0; j < res3.size(); j++){


		std::cout << j << " ";

	}


	std::string s = std::to_string(100);


	



	std::cout << s << " " << s.size() << '\n';
	return 0;
}
