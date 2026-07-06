#include <iostream>
#include <Windows.h>
#include <thread>
#include <chrono>


int main(){
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	if(hConsole == INVALID_HANDLE_VALUE){
		std::cerr << "Could make console\n";
		return 1;
	}

	if (!SetConsoleActiveScreenBuffer(hConsole)){
		std::cerr << "SetConsoleActiveScreenBuffer failed\n";
		CloseHandle(hConsole);
	    return 1;
	}
	CONSOLE_SCREEN_BUFFER_INFO screenInfo{};


	if (!GetConsoleScreenBufferInfo(hConsole, &screenInfo)) {
	   std::cerr << "GetConsoleScreenBufferInfo failed\n";
	   CloseHandle(hConsole);
	   return 1;
	}

	SHORT width = screenInfo.dwSize.X;
	SHORT height = screenInfo.dwSize.Y;

	COORD pos = { 0, 0  };
//	std::string text = "A";
	DWORD bytesWritten = 0;





	const char* text{"A"} ;
	const char* start{" "};

	while(pos.X < width){
		WriteConsoleOutputCharacter(hConsole,start,1,pos,&bytesWritten);

		pos.X++;




		//Sleep(300);
		WriteConsoleOutputCharacter(hConsole,text,1,pos,&bytesWritten);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));


	}




	Sleep(2000);

	CloseHandle(hConsole);
	//std::cout << "Hello, World\n";

	return 0;
}

