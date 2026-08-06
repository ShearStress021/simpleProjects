#include <iostream>
#include "market.hpp"
#include "csvReader.hpp"



int main(){

	CSVReader reader{};
	auto market = reader.readData("data/output.csv");
	std::cout << market.tradesLength() << '\n';

	std::cout << "Hello, World\n";
	return 0;
}
