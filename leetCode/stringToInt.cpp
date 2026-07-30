#include <iostream>
#include <string>



int main(){
	std::string s{" 43"};
	std::string newS{};

	int i{};
	long long res{};
	std::size_t n{s.size()};

	while(i < n && std::isdigit(s[i])){
		int d = s[i] - '0';
		res = res * 10 + d;
		i++;
	}


	std::cout << res << '\n';
	

	return 0;
}

