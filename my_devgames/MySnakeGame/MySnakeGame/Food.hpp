#pragma once



#include "point.hpp"	
#include <vector>


class Food {

public:
	Food(int bandWidth, int boardheight);

	void respawn(const std::vector<Point>& snakeBody);

	Point getPositione() const { return pos; }

private:
	Point pos{};
	int   width{};
	int   height{};

};
