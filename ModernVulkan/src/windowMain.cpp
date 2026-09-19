#include "windowMain.hpp"



bool MainWindow::init(){
	if(!SDL_InitSubSystem(SDL_INIT_VIDEO)){
		Error("Failed to Init SDL3");
		return false;
	}

	window = SDL_CreateWindow("vulkan + SDL3",width,height, SDL_WINDOW_VULKAN | SDL_WINDOW_RESIZABLE);
	if(!window){
		Error("Error in creating window");
		return false;
	}

	


	return true;
}

void MainWindow::Error(const char* msg) const{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", msg,window);
	
}
