#include <iostream>
#include <windows.h>
#include <tlhelp32.h>
#include <winternl.h> // For NtQueryInformationProcess
#include <string>

 #pragma comment(lib, "ntdll.lib")

// Function pointer to NtQueryInformationProcess from ntdll.dll
typedef NTSTATUS (NTAPI *pNtQueryInformationProcess)(
    HANDLE ProcessHandle,
    PROCESSINFOCLASS ProcessInformationClass,
    PVOID ProcessInformation,
    ULONG ProcessInformationLength,
    PULONG ReturnLength
);

bool IsProcessBeingDebugged(HANDLE hProcess) {
    // Load NtQueryInformationProcess from ntdll.dll
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (!hNtdll) return false;

    auto NtQueryInformationProcess = (pNtQueryInformationProcess)GetProcAddress(hNtdll, "NtQueryInformationProcess");
    if (!NtQueryInformationProcess) return false;

    ULONG_PTR debugPort = 0;
    NTSTATUS status = NtQueryInformationProcess(hProcess, ProcessDebugPort, &debugPort, sizeof(debugPort), nullptr);
    
    // If debugPort is not zero, the process is likely being debugged
    return (status == 0 && debugPort != 0);
}

int main() {
    HANDLE pSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    std::wcout << L"Checking all processes for debugging status..." << std::endl;

    // Iterate over all processes
    if (Process32First(pSnap, &entry)) {
        do {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, entry.th32ProcessID);
            if (hProcess != NULL) {
                bool isDebugged = IsProcessBeingDebugged(hProcess);
                if (isDebugged) {
                    std::wcout << L"[DEBUGGED] Process ID: " << entry.th32ProcessID
                               << L"\tProcess Name: " << entry.szExeFile << std::endl;
                }
                CloseHandle(hProcess);
            }
        } while (Process32Next(pSnap, &entry));
    }

    CloseHandle(pSnap);
    return 0;
}
