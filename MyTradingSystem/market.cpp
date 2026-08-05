#include "market.hpp"


Trade::Trade(std::string_view& timeStamp_, 
		float open_, float high_, float low_, float close_, long long volume_) :
		timeStamp(timeStamp_), open(open_), high(high_), low(low_), close(close_), volume(volume_) {

	}



void Trade::validate() const {

	if(timeStamp.empty()){
		throw std::invalid_argument("Timestamp cannot be empty");
	}

	if(open < 0){
		throw std::invalid_argument("Open Cannot be negative");
	}
	if(high < 0){
		throw std::invalid_argument("High Cannot be negative");
	}

	if(low < 0){
		throw std::invalid_argument("Low Cannot be negative");
	}
	if(close < 0){
		throw std::invalid_argument("Close Cannot be negative");
	}
	if(volume < 0){
		throw std::invalid_argument("Volume Cannot be negative");
	}
}



std::string Trade::getTimeStamp() const {
	return timeStamp;
}




