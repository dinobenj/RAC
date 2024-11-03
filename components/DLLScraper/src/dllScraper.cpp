// src/dllScraper.cpp
#include "../include/dllScraper.h"
#include <iostream>
#include <windows.h>
#include <fstream>
#include <codecvt>
#include <locale>

/**
 * @brief Converts a standard string (std::string) to a wide string (std::wstring).
 * This function is used to convert a narrow string to a wide string, which is required
 * by Windows API functions that expect wide character strings (LPCWSTR).
 * 
 * @param str The input string to convert (std::string).
 * @return std::wstring The converted wide string (std::wstring).
 */
std::wstring stringToWString(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

/**
 * @brief Lists all .dll files in a specified folder and writes the list to a specified output file.
 * This function searches for all files with a ".dll" extension in the given folder path,
 * then writes each file name to the output file. It uses Windows API functions for file searching.
 * 
 * @param folderPath The path of the folder where .dll files will be searched (std::string).
 * @param outputFilePath The path of the file where the list of .dll files will be written (std::string).
 * 
 * @details If the folder path is invalid or no .dll files are found, an error message
 * is printed to the console. Similarly, if the output file cannot be opened, an error
 * message is displayed. The function uses wide-character versions of the Windows API
 * functions to handle Unicode file paths.
 * 
 * @return void This function does not return a value.
 */
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
