#pragma once
#include <windows.h>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

struct Vec3 {
	float x,y, z;
};

struct triangle {
	Vec3 p[3];
};

struct Mesh {
	std::vector<triangle> tris{};

};

struct Mat4 {
	float m[4][4]{};
};

	


class Console3d {
	public:
		Console3d() {
			std::cout << "Hello, Console3d\n";
			screenWidth = 130;
			screenHeight = 30;
			handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}

		int initConsoleWindow(){
			if(handleConsole == INVALID_HANDLE_VALUE){
				std::cerr << "Could make Console\n";
				return 1;

			}
			if(!SetConsoleActiveScreenBuffer(handleConsole)){
				std::cerr << "Set ConsoleActiveScreenBuffer failed\n";
				CloseHandle(handleConsole);
				return 1;

			}


			windowRect = {0,0,1,1};
			SetConsoleWindowInfo(handleConsole, TRUE, &windowRect);

			COORD bufferSize{};
			bufferSize = {(short)screenWidth, (short)screenHeight};
			if(!SetConsoleScreenBufferSize(handleConsole, bufferSize)){
				std::cerr << "Set Console Screen Buffer Size failed\n";
				CloseHandle(handleConsole);
				return 1;

			}


			CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
			if(!GetConsoleScreenBufferInfo(handleConsole, &screenInfo)){
				std::cerr << "GetConsoleScreenBufferInfo Failed\n";
				CloseHandle(handleConsole);
				return 1;


			}

			windowRect = {0,0, (short)(screenWidth - 1), (short)(screenHeight -1 )};

			if(!SetConsoleWindowInfo(handleConsole, TRUE, &windowRect)){
				std::cerr << "Set Console Window Info\n";
				return 1;

			}

			screen = new CHAR_INFO[screenWidth * screenHeight];
			memset(screen, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);

			return 0;


		}

		void init(){
			renderer();

		}


		~Console3d(){
			delete [] screen;

		}
	private:
		void renderer(){

			while(!running){
				// screen clearing  
				for(int i{}; i < screenWidth * screenHeight; i++) {
					screen[i].Char.UnicodeChar= ' ';
					screen[i].Attributes = FOREGROUND_GREEN;
				}
				// boarder 
				for(int i {}; i < screenWidth; i++){
					screen[i].Char.UnicodeChar = '=';
					screen[2* screenWidth + i].Char.UnicodeChar= '=';
				}

			
				WriteConsoleOutput(handleConsole, screen, 
												{(short)screenWidth , (short)screenHeight}, {0,0}, &windowRect);

				if (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) running = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
			
		}


	private:
		HANDLE handleConsole{};
		CHAR_INFO * screen{};
		std::uint8_t screenWidth{};
		std::uint8_t screenHeight{};
		DWORD bytesWritten{};
		SMALL_RECT windowRect{};
		bool running{false};
};




