#include "Snake.hpp"
// #include <iostream>	


Snake::Snake(int startX, int startY) :
	currentDir(Direction::RIGHT), nextDir(Direction::RIGHT)
{
	body.push_back({ startX, startY });

}

Point Snake::getHead() const {
	return body.front();
}

void Snake::setDirection(Direction dir) {
	if (dir == Direction::UP && currentDir == Direction::DOWN) return;
	if (dir == Direction::DOWN && currentDir == Direction::UP) return;
	if (dir == Direction::LEFT && currentDir == Direction::RIGHT) return;
	if (dir == Direction::RIGHT && currentDir == Direction::LEFT) return;

	nextDir = dir;
}

void Snake::move() {
	currentDir = nextDir;

	Point newHead = getHead();

	switch (currentDir) {
	case Direction::UP:
		newHead.y -= 1;
		break;
	case Direction::DOWN:
		newHead.y += 1;
		break;
	case Direction::LEFT:
		newHead.x -= 1;
		break;
	case Direction::RIGHT:
		newHead.x += 1;
		break;

	}

	body.insert(body.begin(), newHead);

	body.pop_back();
}

void Snake::grow() {
	body.push_back(body.back());
}

bool Snake::checkSelfCollision() const {
	Point head = getHead();

	for (size_t i{ 1 }; i < body.size(); ++i) {
		if (body[i] == head) return true;

	}
	return false;

}








