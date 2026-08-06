#pragma once


#include "Snake.hpp"
#include "Food.hpp"	


class Game {
public:
	Game(int width, int height);
	void run();


private:
	void  handleInput();
	void update();
	void draw() const;
	bool isGameOver() const;


	Snake snake;
	Food food;

	int boardWidht{};
	int boardHeight{  };
	int score{};
	bool gameOver{};
};