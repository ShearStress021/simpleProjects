#include <iostream>
#include <string>
#include <ranges>


std::string ltrim(const std::string& str){
	std::string s(str);
	s.erase(
			s.begin(),std::ranges::find_if(s, [](unsigned char c){
				return !std::isspace(c);
				})
		   );

	return s;
}

std::string rtrim(const std::string& str){
	std::string s(str);

	s.erase(

			std::ranges::find_if(s, [](unsigned char c){
				return !std::isspace(c);
				}),
			s.begin()
			);
	
	return s;	
}


int main(){

	std::string s = " hello geek";
	std::string p = " hello geek  ";


	std::string x = ltrim(s);
	std::string y = rtrim(s);

	std::cout << "res " << x << '\n';
	std::cout << "back " << y << '\n';
	return 0;
}
