#include <iostream>
#include <vector>

int get_total(int n){
	std::vector<int> tots{2,8};
	std::vector<int> cum{2,10};

	if (n > tots.back()){

		while (tots.back() < n){
			tots.push_back(4 * tots.back() + *(tots.end() - 2));
			cum.push_back(cum.back() + (tots.back()));
		}		
	}

	int maxInd = tots.size() - 1;
	for(int i = maxInd; i >= 0 ; i--){
		if(tots[i] <= n){

			return cum[i];
		}
	}

	return 0;
}






int main(){
	int prev{1};
	int next{2};
	int nth{};
	std::vector<int> nums {1,3,4,6};

	for(int i = 0; i < 15; i++){
		std::cout << prev  << " ";
		nth = prev + next;
		prev = next;
		next = nth;

	}
	std::cout << '\n';

	int s = get_total(100);

	std::cout << "my sum " << s << '\n';
	return 0;
}
