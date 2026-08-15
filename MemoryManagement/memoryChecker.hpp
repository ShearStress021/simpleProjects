#pragma once
#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include "linkedList.h"



struct TreadBasicInfo {
    NTSTATUS exitStatus{};
    PVOID baseAddress{};
    CLIENT_ID clientID{};
    KAFFINITY affinityMask{};
    KPRIORITY priority{};
    LONG basePriority{};
};



void getThreadStack(LinkedList<int>& llst);






