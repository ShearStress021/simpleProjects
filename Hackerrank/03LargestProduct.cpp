#include <algorithm>
#include <iostream>
#include <ranges>





int main(){
	std::string nms;
	std::getline(std::cin, nms);

	int sum {1};
	

	std::for_each(nms.begin(), (nms.begin()) + 5, [&sum](unsigned char c)
			{sum *= (c - '0');});

	std::cout << "first sum" << sum << "\n";

	int k = 5;

	int l = 0;

	int res = sum;

	for (int i = k; i < nms.size(); i++){
		int temp = sum * (nms[i] - '0');
		temp /= (nms[l] - '0');
		std::cout << temp << "\n";
		sum = temp;
		res = std::max(sum, res);

		l++;



	}
	std::cout << sum  << res << '\n';
	
	return 0;
}
