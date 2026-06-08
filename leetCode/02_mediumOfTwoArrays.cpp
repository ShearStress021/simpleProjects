#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>
#include <ranges>


double getMedian(std::vector<int>& nums1, std::vector<int>& nums2){

	int n = nums1.size();
	int m = nums2.size();
	int i{0}, j{0}, m1{0}, m2{0};

	for(size_t x{0}; x < (n + m)/2; x++){
		m1 = m2;
		if(i != n && j != m){
			if(nums1[i] > nums2[j]){
				m2 = nums2[j++];
			} else {
				m2 = nums1[i++];
			}

		} else if(i < n){
			m2 = nums1[i++];
		} else {
			m2 = nums2[j++];
		}
	}

	if((n + m) % 2 == 1){
		return static_cast<double>(m1);
	} else {
		double ans = static_cast<double>(m1) + static_cast<double>(m2);
		return ans / 2.0;
	}

}


int main(){

	std::vector<int> n1{2,2, 4, 4};
	std::vector<int> n2{2, 2, 2, 4,4 };

	std::cout << "Results: " << getMedian(n1, n2) << '\n';
	return 0;
}
