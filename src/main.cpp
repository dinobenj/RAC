#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
//#include <wchar.h>


int main(){
    HANDLE pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    while(Process32Next(pSnap, &entry)){
        std::wcout << L"Process ID: " << entry.th32ProcessID 
               << L"\tProcess Name: " << entry.szExeFile << std::endl;
    }
    CloseHandle(pSnap);
}