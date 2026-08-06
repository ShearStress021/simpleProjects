#include "csvReader.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>




Trade CSVReader::readRow(const std::string& line){
	std::stringstream ss(line);

	std::string timeStamp{};
	std::string open{};
	std::string high{};
	std::string low{};
	std::string close{};
	std::string volume{};
	std::string unknown{};


	if(!std::getline(ss, timeStamp,  ',') ||
			!std::getline(ss, open,  ',') ||
			!std::getline(ss, high,  ',') ||
			!std::getline(ss, low,   ',') ||
			!std::getline(ss, close, ',') ||
			!std::getline(ss, volume, ','))
	{
		throw std::runtime_error("Error on line " + line);
	}

	if(!std::getline(ss, unknown, ',')) 
		throw std::runtime_error("Unknown column "+ line);


	try {
		return Trade {
			timeStamp,
			std::stof(open),
			std::stof(high),
			std::stof(low),
			std::stof(close),
			std::stoll(volume),

		};

	}
	catch (const std::exception&){
		throw std::runtime_error("Failed to parse line " + line);

	}

}


Market CSVReader::readData(const std::string& filepath){

	std::ifstream file(filepath);
	if(!file.is_open()){
		throw std::runtime_error("Failed to open the file " + filepath);
	}

	std::string line{};

	if(!std::getline(file, line))
		throw std::runtime_error("CVS file is empty");



	Market market{};
	while(std::getline(file, line)){
		if(line.empty())
			continue;

		market.addTrade(readRow(line));


	}
	return market;
}





