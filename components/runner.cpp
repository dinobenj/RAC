#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <string>
#include <stdint.h>
#include <iomanip>
#include <cstdint>

//DebugActiveProcess(processId);
// Clear-Host ; g++ -Wall -Wextra .\components\runner.cpp ; ./a.exe
// tasklist /m /fi "imagename eq hl2.exe"

int32_t GetProcessID(const std::string& processName) {
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) { CloseHandle(hProcessSnap); return 0; }

    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hProcessSnap, &pe32)) {
        do {
            if (processName == pe32.szExeFile) {
                CloseHandle(hProcessSnap);
                return pe32.th32ProcessID;
            }
        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);
    return 0;
}

uint32_t GetDLLProcessID(int32_t processID, const std::string& dllToLookFor = "") {
    HANDLE hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, processID);
    if (hModuleSnap == INVALID_HANDLE_VALUE) { return -1; }

    MODULEENTRY32 me32;
    me32.dwSize = sizeof(MODULEENTRY32);

    if (!Module32First(hModuleSnap, &me32)) { CloseHandle(hModuleSnap); return -1; }

    do {
        std::wcout << L"Module Name: " << me32.szModule << std::endl;
        if (me32.szModule == dllToLookFor) {
            CloseHandle(hModuleSnap);
            return *me32.modBaseAddr;
        }
    } while (Module32Next(hModuleSnap, &me32));

    CloseHandle(hModuleSnap);
    return -1;
}

int main() {
    // Get process for CSSource and print i
    int32_t processId = GetProcessID("hl2.exe");
    if (processId == 0) {
        std::cerr << "Failed to find Counter Strike Source" << std::endl;
        return 1;
    }
    std::cout << "Process ID: " << processId << std::endl;

    std::cout << "Client.dll: " << GetDLLProcessID(processId, "client.dll"); << std::endl;

    return 0;
}