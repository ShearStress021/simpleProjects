#include <iostream>
#include <array>
#include <string>


std::string intToRoman(int number){
	std::string res{};
	std::array<std::string, 13> sym{"I", "IV","V", "IX", "X", "XL", "L", "XC", "C", "CD", "D","CM", "M"};
	std::array<int, 13> nums {1,4,5,9,10,40,50,90,100,400,500,900,1000};

	int i{12};

	while(number > 0 ) {
		int div = number / nums[i];
		number %= nums[i];

		while(div > 0) {
			res += sym[i];
			div -= 1;
		}
		i -= 1;
	}
	return  res;
}


int main(){

	int num{1994};
	std::cout << intToRoman(num) << '\n';

	return 0;

}







