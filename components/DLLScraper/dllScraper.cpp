#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <codecvt>  // For string conversion
#include <locale>

// Convert std::string to std::wstring
std::wstring stringToWString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

void listDll(const std::string& folderPath, const std::string& outputFilePath) {
    WIN32_FIND_DATAW fileData;
    HANDLE hFind;

    // Open the file stream for writing
    std::ofstream outputFile(outputFilePath);
    
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        return;
    }

    // Convert folderPath to wide string and append the search pattern
    std::wstring searchPath = stringToWString(folderPath + "\\*.dll");

    // Use the wide version of FindFirstFile
    hFind = FindFirstFileW(searchPath.c_str(), &fileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No .dll files found or invalid folder path." << std::endl;
        return;
    }

    // Loop through and write all .dll files to the file
    do {
        outputFile << std::wstring(fileData.cFileName).c_str() << std::endl;
    } while (FindNextFileW(hFind, &fileData) != 0);

    // Close the handle and the file
    FindClose(hFind);
    outputFile.close();

    std::cout << "DLL list has been written to: " << outputFilePath << std::endl;
}
