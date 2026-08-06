#include "market.hpp"
#include <stdexcept>


Trade::Trade(std::string& timeStamp_, 
		float open_, float high_, float low_, float close_, long long volume_) :
		timeStamp(timeStamp_), open(open_), high(high_), low(low_), close(close_), volume(volume_) {

	}
[[nodiscard]] bool Trade::validate() const {
	if(timeStamp.empty()){
		throw std::invalid_argument("Timestamp cannot be empty");
		return false;
	}

	if(open < 0){
		throw std::invalid_argument("Open Cannot be negative");
		return false;
	}
	if(high < 0){
		throw std::invalid_argument("High Cannot be negative");
		return false;
	}

	if(low < 0){
		throw std::invalid_argument("Low Cannot be negative");
		return false;
	}
	if(close < 0){
		throw std::invalid_argument("Close Cannot be negative");
		return false;
	}
	if(volume < 0){
		throw std::invalid_argument("Volume Cannot be negative");
		return false;
	}
	return true;
}

std::string Trade::getTimeStamp() const{
	return timeStamp ;
}

float Trade::getOpen() const {
	return open;
}

float Trade::getHigh() const {
	return high;
}

float Trade::getLow() const {
	return low;
}

float Trade::getClose() const {
	return close;
}
long long Trade::getVolume() const {
	return volume;
}


void Market::addTrade(const Trade& trade){
	trades.push_back(trade);
}


const Trade & Market::getTrade(std::size_t index) const{
	if(index >= trades.size() - 1)
		throw std::invalid_argument("index provide bigger than trades list len");

	return trades[index];
}

std::size_t Market::tradesLength() const{
	return trades.size();
}













