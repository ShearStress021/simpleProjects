#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

bool validParenthesis(std::string_view s){
	std::vector<char> res{};
	std::unordered_map<char, char> map{
		{')' , '('}, {']' , '['}, {'}', '{'}
	};

	for(char c: s){
		if(map.contains(c)){
			char top = (res.empty()) ? 'r' : res.back();
			if(!res.empty()) res.pop_back();
			if(map[c] != top) return false;
		}else res.push_back(c);
	}



	return res.empty();
}


int main(){

	std::string s{"({[]})"};
	std::cout << validParenthesis(s);
	return 0;
}
