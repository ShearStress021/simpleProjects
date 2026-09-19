#include <iostream>
#include <Windows.h>

LRESULT CALLBACK WndProc(HWND window, UINT msg, WPARAM wp, LPARAM lp){
	LRESULT Result{};
	switch(msg){
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_PAINT:
		{
			PAINTSTRUCT paint{};
			HDC deviceContext = BeginPaint(window,&paint);
			EndPaint(window,&paint);
			break;
		 }
		case WM_CREATE:
		  {

		  }
		
				



		default:
			Result = DefWindowProc(window,msg,wp,lp);
	}
	return Result;
}



int main(){
	//HWND hwnd{};
	HINSTANCE instance = GetModuleHandle(NULL);

	WNDCLASS wClass{};
	char windowName[] = "3D Cube";
	wClass.lpszClassName = windowName;
	wClass.lpfnWndProc =  WndProc;
	wClass.hInstance = instance;
	if (!RegisterClass(&wClass)) /*Register a Class*/
	{
		MessageBox(NULL, "Window registration failed ", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 1;

	}



	// Create window
	HWND hwnd = CreateWindowEx(0,windowName,"3d cube app", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX ,500, 500,400, 300,
			nullptr,nullptr,instance,nullptr);

	if (hwnd == NULL){
		MessageBox(NULL, "Window creation failed", "Error", MB_ICONEXCLAMATION | MB_OK);
		return 1;
	}

	ShowWindow(hwnd,1);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg); /*Translates Keyboard messages in to characters.Nesscary For user input*/
		DispatchMessage(&msg);  /*send the message to the window procedure*/

	}

	//std::cout << "Hello, World\n";
	return 0;
}

