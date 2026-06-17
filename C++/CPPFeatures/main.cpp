#include <iostream>
#include <string>
#include <array>

template<typename T1, typename T2>
class Geek{
	private:
		T1 x;
		T1 y;
		T2 c;

	public:

		Geek(T1 v1, T1 v2, T2 v3 ):
			x(v1), y(v2), c(v3) {

			}
		int maxVal(){
			return (x > y) ? x : y;
		}
	
		void getString(){
			std::cout << "String: " << c << '\n';
		}



};


template<typename T>
int arrMin(std::array<T, 5> arr){
	int m = arr[0];

	for(int i = 1; i < 5 ; i++){
		m = (m < arr[i]) ? m : arr[i];
	}
	return m;
}


int main(){

	std::array<int, 5> arr { 10, 8, 20,16, 4};
	std::cout << "min int: " << arrMin(arr) << '\n';
	return 0;
}
