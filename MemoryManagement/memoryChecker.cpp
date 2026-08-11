#include "memoryChecker.hpp"
#include <iostream>

void  getThreadStack(LinkedList<int>& llst){
    DWORD pid = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);

    if(snapshot == INVALID_HANDLE_VALUE) return;
    THREADENTRY32 te{};

    if (Thread32First(snapshot, &te)){
        do {


        } while(Thread32Next(snapshot, &te));

    }

    CloseHandle(snapshot);
    return ;
}


