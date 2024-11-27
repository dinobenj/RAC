// dotnet build ; dotnet run

using System;
using System.Diagnostics;
using System.Runtime.InteropServices;

class Program
{    
    [DllImport("kernel32.dll")]
    public static extern IntPtr OpenProcess(int dwDesiredAccess, bool bInheritHandle, int dwProcessId);

    [DllImport("kernel32.dll", SetLastError = true)]
    public static extern bool ReadProcessMemory(IntPtr hProcess, IntPtr lpBaseAddress, byte[] lpBuffer, uint nSize, out int lpNumberOfBytesRead);

    [DllImport("kernel32.dll")]
    public static extern bool CloseHandle(IntPtr hObject);

    const int PROCESS_VM_READ = 0x0010;
    const int PROCESS_QUERY_INFORMATION = 0x0400;

    // given "hl2" it will find the process ID for Counter Strike Source
    static int getProcessID(string targetProcessName) {
        Process[] processMain = Process.GetProcessesByName(targetProcessName);

        if (processMain.Length == 0) {
            Console.WriteLine($"{targetProcessName}.exe wasn't found.");
            return -1;
        }
        Console.WriteLine($"Process ID: {processMain[0].Id}, Process Name: {processMain[0].ProcessName}.exe"); // assume there is only 1 process
        return processMain[0].Id;
    }

    // If a dll is loaded from steamapps, check if it is the modulo from the function parameter
    static int getModuleBaseAddress(int processID, string moduleName) {
        Process process = Process.GetProcessById(processID);
        foreach (ProcessModule module in process.Modules) {
            if (module.FileName.Contains("steamapps") && module.ModuleName.EndsWith(moduleName, StringComparison.OrdinalIgnoreCase)) {
                Console.WriteLine($"name = {module.FileName}, Base Address = 0x{module.BaseAddress.ToString("x")}");
                return module.BaseAddress.ToInt32();
            }
        }
        Console.WriteLine($"{moduleName} wasn't found.");
        return 0;
    }

    static (bool, int) ReadMemory32(int processID, int address) {
        IntPtr hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, false, processID);
        byte[] buffer = new byte[4];
        int bytesRead;

        if (ReadProcessMemory(hProcess, (IntPtr)address, buffer, (uint)buffer.Length, out bytesRead) && bytesRead == buffer.Length) {
            int playerPointer = BitConverter.ToInt32(buffer, 0);
            CloseHandle(hProcess);
            return (true, playerPointer);
        }
        Console.WriteLine($"Failed to read memory on ProcessID: {processID} at address {address.ToString("x")}");
        CloseHandle(hProcess);
        return (false, 0);
    }

    static void Main(string[] args)
    {
        int CSS_id = getProcessID("hl2");
        if (CSS_id == -1) { return; }

        // Get location of Client.dll
        int clientDllBaseAddress = getModuleBaseAddress(CSS_id, "client.dll");
        if (clientDllBaseAddress == 0) { return; }

        // Read player pointer location
        int playerPointerLocation = clientDllBaseAddress + 0x4C88E8;
        var infoFromRead = ReadMemory32(CSS_id, playerPointerLocation);
        if (infoFromRead.Item1 == false) { return; }
        Console.WriteLine($"Player Pointer Location: 0x{playerPointerLocation.ToString("x")}, Player Pointer: 0x{infoFromRead.Item2.ToString("x")}");

        // Read health as a test
        int healthAddress = infoFromRead.Item2 + 0x0094;
        var healthFromRead = ReadMemory32(CSS_id, healthAddress);
        if (healthFromRead.Item1 == false) { return; }
        Console.WriteLine($"Health Address: 0x{healthAddress.ToString("x")}, Health: {healthFromRead.Item2}");
    }
}