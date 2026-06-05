#include <windows.h>
#define static local_persist
#define static global_variable


global_variable bool running;


LRESULT CALLBACK mainWindowCallBack(
		  HWND    window,
		  UINT    message,
		  WPARAM  wParam,
		  LPARAM  lParam
				  
		)
{

	LRESULT Result = 0;

	switch(message){
		case WM_SIZE:
			{
				break;
			}
		case WM_DESTROY:
			{
				running = false;
				break;
			}
		case WM_CLOSE:
		{
			running = false;
			break;
		}
		case WM_ACTIVATEAPP:
		{
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT paint;

			HDC DeviceContext = BeginPaint(window, &paint);
			int X = paint.rcPaint.left;
			int Y = paint.rcPaint.top;
			int Height = paint.rcPaint.bottom - paint.rcPaint.top;
			int Width = paint.rcPaint.right - paint.rcPaint.left;
			local_persist DWORD Operation = WHITENESS;
			PatBlt(DeviceContext, X, Y, Width, Height, Operation);
			if(Operation == WHITENESS) {
				Operation = BLACKNESS;
			}
			else {
				Operation = WHITENESS;
			}
			EndPaint(window, &paint);
			break;
		}
		default:
		{
			Result = DefWindowProc(window, message, wParam, lParam);
		}
	}
	
	return (Result);

}
int CALLBACK WinMain(HINSTANCE instance, HINSTANCE previousInstance, PSTR cmdline, int showcode) {
	WNDCLASS  WindowClass = {};
    WindowClass.style = CS_OWNDC| CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = mainWindowCallBack ;
	WindowClass.hInstance = instance;
//	HICON     hIcon;
//	HCURSOR   hCursor;
//	HBRUSH    hbrBackground;
  //  LPCSTR    lpszMenuName;
	WindowClass.lpszClassName = "Playing with cpu";

	if(RegisterClass(&WindowClass)){

		HWND  windowHandle = CreateWindowEx(
		   	0, 
		    WindowClass.lpszClassName,
			"Playing with cpu",
		    WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		    CW_USEDEFAULT,
		    CW_USEDEFAULT,
		    CW_USEDEFAULT,
		    CW_USEDEFAULT,
		    0,
		    0,
		    instance,
		    0);

		if(windowHandle){
			MSG message;
			while(running){
				BOOL MessageResult = GetMessage(&message, 0,0,0);
				if(MessageResult > 0){

					TranslateMessage(&message);
					DispatchMessage(&message);

				}
				else {
					break;
				}
			}
		}
		else {

		}

	}
	else {

	}
	return 0;
			
}
