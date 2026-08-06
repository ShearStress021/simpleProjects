#pragma once
#include <string>
#include <vector>


class Trade {

	public:
		Trade(std::string& timeStamp_, 
				float open_, 
				float high_, 
				float low_, 
				float close_, 
				long long volume_
				);

		std::string getTimeStamp() const;
		float getOpen() const ;
		float getClose() const ;
		float getHigh() const ;
		float getLow() const ;
		long long getVolume() const ;
		


	private:
		std::string timeStamp{};
		float open{};
		float high{};
		float low{};
		float close{};
		long long volume{};
		[[nodiscard]] bool validate() const;
};


class Market {
	public:
		Market() = default;
		void addTrade(const Trade& trade) ;
		bool empty() const;
		size_t tradesLength() const;
		const Trade& getTrade(size_t index) const;
	private:
		std::vector<Trade> trades{};
};
