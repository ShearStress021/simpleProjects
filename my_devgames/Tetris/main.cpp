#include <iostream>
#include <Windows.h>


const int screenWidth{80} ;
const int screenHeight{30};
std::wstring tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
unsigned char *pField = nullptr;

int main(){
	HANDLE screenConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	DWORD byteWritten{};
	if(screenConsole == INVALID_HANDLE_VALUE){
		std::cerr << "Could make console\n";
		return 1;

	}
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


	// Variable 
	wchar_t *screen = new wchar_t[screenWidth * screenHeight];
	for(int i{}; i < screenWidth; i++) screen[i] = L' ';
	tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	pField = new unsigned char[nFieldWidth*nFieldHeight]; // Create play field buffer
	for (int x = 0; x < nFieldWidth; x++) // Board Boundary
		for (int y = 0; y < nFieldHeight; y++)
			pField[y*nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;


	bool gameOver{false};
	bool quitGame{false};

	while(!gameOver){

		// Draw Field
		for (int x = 0; x < nFieldWidth; x++)
			for (int y = 0; y < nFieldHeight; y++)
				screen[(y + 2)*screenWidth + (x + 2)] = L" ABCDEFG=#" [pField[y*nFieldWidth + x]];









		WriteConsoleOutputCharacterW(screenConsole,screen,screenWidth * screenHeight, {0,0}, &byteWritten);






		quitGame = (GetAsyncKeyState((unsigned char)('\x20')) & 0x8000) != 0;
		if(quitGame) gameOver = true;
	}





	CloseHandle(screenConsole);
	return 0;
}
