#pragma once
#define NOMINMAX 1
#include <windows.h>
#include <cstdint>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <algorithm>


struct Vec3 {
	float x,y, z;
};

struct Points{
	Vec3 p[3];
};

struct Mesh {
	std::vector<Points> triangle{};

};

struct Mat4 {
	float mat[4][4]{};


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
		void drawLine(int x1, int y1, int x2, int y2, short c = 'o', short color = 0x0009){
			int dx = std::abs(x2 - x1);
			int dy = std::abs(y2 - y1);

			int x = x1;
			int y = y1;

			int cx = (x1 < x2) ? 1 : -1;
			int cy = (y1 < y2) ? 1 : -1;
	

			draw(x,y,c,color);
			
			// slope (dy/dx) <= 1;
			if(dx  >= dy){
				// decision parameter
				int P = ((2*dy) - dx);
				while(x != x2){
					if (P < 0){
						x += cx;
						draw(x, y, c, color);
						P = P + 2 * dy;
					} else {
						x+=cx; y+= cy;
						draw(x, y, c, color);
						P = P + 2 * dy - 2 * dx;
					}

				}
			}else {    // slope (dy/dx) > 1;
			    int P = ((2 *dx) - dy);
				while(y != y2){
					if(P < 0){
						y += cy;
						draw(x, y, c, color);
						P = P + 2 * dx;
					}
					else {
						x += cx, y += cy;
						draw(x,y,c , color);
						P = P + 2 * dx - 2 * dy;
					}

				}


			}



		}
		void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, short chr = 'o', short color = 0x000f){
			drawLine(x1, y1, x2, y2,chr,color);
			drawLine(x2, y2, x3, y3,chr,color);
			drawLine(x1, y1, x3, y3,chr,color);
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

				createPerspectiveMatrix();

				drawCube();

//


				//drawTriangle(30,10,20,20,50,20);
			//drawLine(30,10,10,20);
				


			
				WriteConsoleOutput(handleConsole, screen, 
												{(short)screenWidth , (short)screenHeight}, {0,0}, &windowRect);

				if (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) running = true;
				std::this_thread::sleep_for(std::chrono::milliseconds(200));
			}
			
		}
		void multiplyMat4Vec3(const Vec3 &v, Vec3 &res, Mat4 &m) {
			res.x = v.x * m.mat[0][0] + v.y * m.mat[1][0] + v.z * m.mat[2][0] + m.mat[3][0];
			res.y = v.x * m.mat[0][1] + v.y * m.mat[1][1] + v.z * m.mat[2][1] + m.mat[3][1];
			res.z = v.x * m.mat[0][2] + v.y * m.mat[1][2] + v.z * m.mat[2][2] + m.mat[3][2];
			float w = v.x * m.mat[0][3] + v.y * m.mat[1][3] + v.z * m.mat[2][3] + m.mat[3][3];


			if(w != 0.f){
				res.x /= w;
				res.y /= w;
				res.z /= w;
			}
		}

		void createPerspectiveMatrix(){
			float nearPlane{0.1f};
			float farPlane{100.f};
			float aspectRatio {static_cast<float>(screenHeight)/static_cast<float>(screenWidth)};
			float fieldOfView{90.f};
			float fieldOfViewRad{1.0f/std::tanf(fieldOfView * 0.5 * 3.14159f / 180)};

			matrixProj.mat[0][0] = aspectRatio * fieldOfView;
			matrixProj.mat[1][1] = fieldOfViewRad;
			matrixProj.mat[2][2] =  farPlane / (farPlane - nearPlane);
			matrixProj.mat[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
			matrixProj.mat[2][3] = 1.0f;
			matrixProj.mat[3][3] = 0.0f;
		}

		void drawCube(){
			vertex.triangle =  {
				// SOUTH
				{ 0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f  },
				{ 0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f  },

				// EAST                                                      
				{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f  },
				{ 1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f  },
				//
				// NORTH                                                     
				{ 1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f  },
				{ 1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f  },
				//
				// 						// WEST                                                      
				{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f  },
				{ 0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f  },
				//
				// TOP                                                       
				{ 0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f  },
				{ 0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f  },
				
				//Bottom
				{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f  },
				{ 1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f  },

			};

			for (auto tri : vertex.triangle) {
				Points projPoints, translated;
				translated.p[0].z = tri.p[0].z + 3.f;
				translated.p[1].z = tri.p[1].z + 3.f;
				translated.p[2].z = tri.p[2].z + 3.f;

				

				multiplyMat4Vec3(translated.p[0], projPoints.p[0], matrixProj);
				multiplyMat4Vec3(translated.p[1], projPoints.p[1], matrixProj);
				multiplyMat4Vec3(translated.p[2], projPoints.p[2], matrixProj);


				projPoints.p[0].x += 1.f; projPoints.p[0].y += 1.f;
				projPoints.p[1].x += 1.f; projPoints.p[1].y += 1.f;
				projPoints.p[2].x += 1.f; projPoints.p[2].y += 1.f;

				projPoints.p[0].x *= 0.5f * static_cast<float>(screenWidth);
				projPoints.p[0].y *= 0.5f * static_cast<float>(screenHeight);
				projPoints.p[1].x *= 0.5f * static_cast<float>(screenWidth);
				projPoints.p[1].y *= 0.5f * static_cast<float>(screenHeight);
				projPoints.p[2].x *= 0.5f * static_cast<float>(screenWidth);
				projPoints.p[2].y *= 0.5f * static_cast<float>(screenHeight);

				drawTriangle(projPoints.p[0].x, projPoints.p[0].y, projPoints.p[1].x, projPoints.p[1].y,
						projPoints.p[2].x, projPoints.p[2].y,'o', 0x0009);

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
		Mesh vertex{};
		Mat4 matrixProj{};
};




