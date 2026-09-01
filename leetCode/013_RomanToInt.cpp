#include <iostream>
#include <unordered_map>
#include <string>


int romanToInt(std::string_view s){
	int res{};
	std::unordered_map<char, int> map {
		{'I', 1},{'V', 5},{'X', 10}, {'L', 50},{'C',100},{'D', 500}, {'M', 1000}
	};

	for(int i{}; i < s.size() - 1; i++){

		if (map[s[i]] < map[s[i + 1]]) res -= map[s[i]];
		else res += map[s[i]];

	}
	



	return res + map[s[s.size() - 1]];
}


int main(){

	std::string s{"MCMXCIV"};

	std::cout << romanToInt(s) << '\n';

}

