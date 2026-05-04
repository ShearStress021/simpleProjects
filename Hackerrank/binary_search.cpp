#include <iostream>
#include <vector>


void binary(std::vector<int> nums, int target){

	int high = nums.size() - 1;
	int low = 0;


	while(low <= high){
		int mid = (low + high)/ 2;

		if(nums[mid] == target){
			std::printf("Element on index %d\n", mid);
		}
		if (target < nums[mid]){
			high = mid -1;
		}else {
			low = mid + 1;
		}


	}


}

int binary1(std::vector<int> nums, int low, int high, int target){


	while(low <= high){
		int mid = (low + high)/2;

		if (nums[mid] == target){
			return mid;
		}

		if (target < nums[mid]){
			return binary1(nums,low, mid - 1, target);
		}
		return binary1(nums, mid + 1, high, target);
		
	}

	return -1;
}


int main(){
	std::vector<int> nums{1,2,4,5,6,7,9,10,15,16};
	int target{10};
	int n = nums.size();

	binary(nums, target);
	int res = binary1(nums, 0, n-1,target); 
	std::printf("Element at index %d is %d\n", res, nums[res]);
	return 0;
}
