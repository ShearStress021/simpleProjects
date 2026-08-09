#include <iostream>
#include <vector>

std::vector<int> gradingStudents(std::vector<int> grades){
	std::vector<int> res{};

	for(auto grade : grades){
		int num = grade / 5;
		int newGrade = num * 5;
		if (grade < 38){
			res.push_back(grade);
		} else {
			int diff = 5 - (grade % 5);

			if (diff < 3){
				res.push_back(grade + diff);
			}else {
				res.push_back(grade);
			}

		}
	}

	return res;
}

int main(void){

	std::vector<int> grades{73,67,38,33};

	auto res = gradingStudents(grades);

	for(auto r: res){
		std::cout << r << '\n';
	}

}
