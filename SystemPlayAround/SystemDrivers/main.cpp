#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <Windows.h>
#include <psapi.h>


struct DriverInfo {
	std::string baseName{};
	//std::string fileName{};
	uintptr_t loadAddress{};
};



[[nodiscard]] std::vector<DriverInfo> getDrivers(){

	std::vector<DriverInfo> myList{};
	LPVOID drivers[1024]{nullptr};
	DWORD bytesNeeded{};

	if((EnumDeviceDrivers(drivers, sizeof(drivers), &bytesNeeded) && bytesNeeded ) > 0){
		size_t count{bytesNeeded/ sizeof(LPVOID)};
		if(count > 1024) count = 1024;
		myList.reserve(count);

		for(size_t i{}; i < myList.size(); i++){
			if(!drivers[i]) continue;

		char baseName[256]{0};
		//char fileName[]


		GetDeviceDriverBaseNameA(drivers[i],baseName,sizeof(baseName));
		//GetDeviceDriverFileName(drivers[i], fileName,sizeof(fileName))
		DriverInfo infoD{};
		infoD.baseName = (baseName[0] == '\0') ? "kernel Sys" : baseName;
		infoD.loadAddress = reinterpret_cast<uintptr_t>(drivers[i]);

		myList.push_back(infoD);

		}

	}



	return myList;


}



int main(){
	std::cout << "Hello, World\n";

	auto results = getDrivers();

	std::cout << results.size() << '\n';

	for(auto res: results){
		std::cout << res.baseName << '\n';
		std::cout << res.loadAddress<< '\n';
	}


	return 0;
}
