#include <iostream>
#include <Windows.h>
#include <string>
#include <cstdint>
#include <vector>
#include <chrono>

using namespace std::chrono_literals;


uint8_t screenWidth{120};
uint8_t screenHeight{30};

struct Snake {
	int x;
	int y;
};


int main(){
	HANDLE screenConsole = 
		CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	DWORD bytesWritten = 0;

	wchar_t *screen = new wchar_t[screenWidth * screenHeight];

	for(int i{}; i < screenWidth * screenHeight; i++) screen[i] = L' ';
	


	if (!SetConsoleActiveScreenBuffer(screenConsole)){
		std::cerr << "SetConsoleActiveScreenBuffer failed\n";
		CloseHandle(screenConsole);
		return 1;
	}
	CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
	if (!GetConsoleScreenBufferInfo(screenConsole, &screenInfo)) {
		std::cerr << "GetConsoleScreenBufferInfo failed\n";
		CloseHandle(screenConsole);
		return 1;
	}

	SHORT width = screenInfo.dwSize.X;
	SHORT height = screenInfo.dwSize.Y;

	while(1){

		std::vector<Snake> snake = { {60,15},{61,15},{62,15},{63,15},{64,15},
			{65,15},{66,15},{67,15},{68,15},{69,15} };

		bool isDead{false};
		int score{};
		int snakeDirection{3};
		bool keyLeft{false};
		bool keyRight{false};
		bool keyLeftOld{false};
		bool keyRightOld{false};

		while(!isDead){

			auto t1 = std::chrono::system_clock::now();
			while((std::chrono::system_clock::now() - t1) < ((snakeDirection % 2 == 1) ? 120ms : 200ms)){
				keyRight = (GetAsyncKeyState((unsigned char)('\x27')) & 0x8000) != 0;
				keyLeft = (GetAsyncKeyState((unsigned char)('\x25')) & 0x8000) != 0;

				if(keyRight && !keyRightOld){
					snakeDirection++;
					if (snakeDirection == 4) snakeDirection = 0;
				}

				if (keyLeft && !keyLeftOld){
					snakeDirection--;
					if(snakeDirection == -1 ) snakeDirection = 3;
				}

				keyLeftOld = keyLeft;
				keyRightOld = keyRight;

			}

			//  ------- Logic
			//
			switch(snakeDirection){
				case 0:
					snake.insert(snake.begin(), {snake.front().x, snake.front().y - 1});
					break;
				case 1:
					snake.insert(snake.begin(), {snake.front().x + 1, snake.front().y });
					break;
				case 2:
					snake.insert(snake.begin(), {snake.front().x , snake.front().y + 1 });
					break;
				case 3:
					snake.insert(snake.begin(), {snake.front().x - 1 , snake.front().y  });
					break;


			}
			// clear screen
			for(int i = 0; i < screenWidth * screenHeight ; i++) screen[i] = L' ';


			// Draw stats & borders
			for(int i = 0; i < screenWidth; i++){
				screen[i] = L'=';
				screen[2 * screenWidth + i] = L'=';
			}

			wsprintfW(&screen[screenWidth + 5], L"Current SNAKE!!!        Score: %d", score);

			// Draw Snake 
			// body
			for(auto s: snake)
				screen[s.y * screenWidth + s.x] = isDead ? L'+' : L'O';

			// Head
			screen[snake.front().y * screenWidth + snake.front().x] = isDead ? L'X' : L'@';



			WriteConsoleOutputCharacterW(screenConsole, screen, screenWidth * screenHeight, {0, 0}, &bytesWritten);
		}

		while((GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) == 0);


	}


	std::cout << "Hello, World\n";
	return 0;
}

