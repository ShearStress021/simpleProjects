#pragma once
#define NOMINMAX
#include <windows.h>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <math.h>
#include <algorithm>


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

		void draw(int x, int y, short c = 0x8000, short color = 0x000F){
			if(x>= 0 && x < screenWidth && y >= 0 && y < screenHeight){
				screen[y * screenWidth + x].Char.UnicodeChar = c;
				screen[y * screenWidth + x].Attributes = color;

			}

		}

		void drawLinee(int x1, int y1, int x2, int y2, short c = '/', short color = 0x0009){
			int dx = x2 - x1;
			int dy = y2 - y1;

			float length = std::sqrt(dx * dx + dy * dy);
			float xstep = dx / length;
			float ystep = dy / length;

			for(float i = 0; i <= length;i += 1.0f){
				int x = static_cast<int>(x1 + xstep * i);
				int y = static_cast<int>(y1 + ystep * i);

				draw(x, y, 'o', color);
			}

		}
		void fillColor(int x1, int y1, int x2,int y2, short c = '-', short color = 0x000F){
			clip(x1, y1);
			clip(x2,y2);

			for(int x = x1; x < x2; x++){
				for(int y = y1; y < y2; y++)
					draw(x,y,c,color);
			}
		}

		void clip(int &x, int &y){
			if(x < 0) x = 0;
			if(x >= screenWidth) x = screenWidth;
			if(y < 0) y = 0;
			if(y >= screenHeight) y = screenHeight;

		}
		void drawLineN(int x1, int y1, int x2, int y2, short c = 'o', short color = 0x0009){
			int dx = std::abs(x2 - x1);
			int dy = std::abs(y2 - y1);

			int x = std::min(x1, x2);
			int y = std::min(y1, y2);
			int xe = std::max(x1, x2);
			int ye = std::max(y1, y2);
	

			draw(x,y,c,color);
			
			// slope (dy/dx) <= 1;
			if(dx  >= dy){
				// decision parameter
				int P = ((2*dy) - dx);
				while(x != xe){
					if (P < 0){
						x += 1;
						draw(x, y, c, color);
						P = P + 2 * dy;
					} else {
						x+=1; y+= 1;
						draw(x, y, c, color);
						P = P + 2 * dy - 2 * dx;
					}

				}
			}else {    // slope (dy/dx) > 1;
			    int P = ((2 *dx) - dy);
				while(y != ye){
					if(P < 0){
						y += 1;
						draw(x, y, c, color);
						P = P + 2 * dx;
					}
					else {
						x += 1, y += 1;
						draw(x,y,c , color);
						P = P + 2 * dx - 2 * dy;
					}

				}


			}



		}
		void drawLine(int x1, int y1, int x2, int y2, short c = 0x2588, short color = 0x000F){
			int dx = std::abs(x2 - x1);
			int dy = std::abs(y2 - y1);

			int sx = (x1 < x2) ? 1 : -1;
			int sy = (y1 < y2) ? 1 : -1;

			int error = dx - dy;

			while(true){
				draw(x1, y1, c, color);
				
				if(x1 == x2 && y1 == y2) break;
				
				int e2 = 2 * error;

				if(e2 > -dy){
					error -= dy;
					x1 += sx;
				}
				if(e2 < dx){
					error += dx;
					y1 += sy;
				}
			}
		}
		void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short chr = 'o', short color = 0x000f){
			drawLineN(x1, y2, x2, y2);
			drawLineN(x2, y2, x3, y3);
			drawLineN(x3, y3, x1, y1);
		}

		void drawline(int x1, int y1, int x2, int y2, short c=0x2588, short color=0x000F){
			int x, y, dx, dy, dx1, dy1, px, py, xe, ye,i;
			dx = x2 - x1; dy= y2 - y1;
			dx1 = abs(dx); dy1 = abs(dy);
			px = 2 * dy1 - dx1; py = 2 * dx1 - dy1;
			if(dy1 <= dx1){
				if(dx >= 0){
					x = x1; y = y1; xe = x2;
				}else {
					x = x2; y = y2; xe = x1;
				}
				draw(x, y,c, color);

				for(i = 0; x < xe; i++){
					x += 1;
					if(px < 0) px = px + 2 * dy1;
					else {
						if((dx < 0 && dy < 0 ) || (dx > 0 && dy > 0)) y+=1;
						else y -= 1;
						px = px + 2 * (dy1 - dx1);
					}
					draw(x, y, c, color);
				}

			} else {
				if(dy >= 0){
					x = x1; y = y1; ye = y2;
				}else {
					x = x2; y = y2; ye = y1;
				}
				draw(x,y,c,color);

				for(i = 0; y < ye; i++){
					y += 1;
					if(py <= 0)
						py = py + 2 * dy1;
					else {
						if((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x+=1; 
						else x -= 1;
						py = py + 2 * (dx1 - dy1);

					}
					draw(x, y, c, color);
				}
			}
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
				//
				fillColor(0,0,screenWidth, screenHeight, ' ',0x000F);
				//for(int i{}; i < screenWidth * screenHeight; i++) {
				//	screen[i].Char.UnicodeChar= ' ';
				//	screen[i].Attributes = FOREGROUND_GREEN;
				//}
				// boarder 
				for(int i {}; i < screenWidth; i++){
					screen[i].Char.UnicodeChar = '=';
					screen[2* screenWidth + i].Char.UnicodeChar= '=';
				}

				drawLineN(30,20,50,20);
				drawLineN(20,10,50,20);
				drawLineN(20,10,30,20);
//


				//drawTriangle(20, 10,30,20,50,20);


			
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




