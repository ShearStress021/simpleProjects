#pragma once
#include "market.hpp"



class CSVReader {
	public:
		static Market readData(const std::string& filepath);
	private:
		static Trade readRow(const std::string& line);
};
