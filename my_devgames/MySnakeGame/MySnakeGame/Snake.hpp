#pragma once


#include "Point.hpp"
#include <vector>


enum class Direction {
	UP, DOWN, LEFT, RIGHT
};


class Snake {
public:
	Snake(int startX, int startY);
	void setDirection(Direction dir);
	void move();
	void grow();

	const std::vector<Point>& getBody() const { return body; }
	Point getHead() const;
	bool checkSelfCollision() const;

private:
	std::vector<Point> body{};
	Direction currentDir{  };
	Direction nextDir{  };
};