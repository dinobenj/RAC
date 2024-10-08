#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>  // For file handling

void listDll(const std::string& folderPath, const std::string& outputFilePath) {
    WIN32_FIND_DATA fileData;
    HANDLE hFind;

    // Open the file stream for writing
    std::ofstream outputFile(outputFilePath);
    
    if (!outputFile.is_open()) {
        std::cerr << "Failed to open output file: " << outputFilePath << std::endl;
        return;
    }

    // Correct the search pattern to find all .dll files
    std::string searchPath = folderPath + "\\*.dll";

    // Correctly call FindFirstFile
    hFind = FindFirstFile(searchPath.c_str(), &fileData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "No .dll files found or invalid folder path." << std::endl;
        return;
    }

    // Loop through and write all .dll files to the file
    do {
        outputFile << fileData.cFileName << std::endl;
    } while (FindNextFile(hFind, &fileData) != 0);

    // Close the handle and the file
    FindClose(hFind);
    outputFile.close();

    std::cout << "DLL list has been written to: " << outputFilePath << std::endl;
}

int main() {
    std::string folderPath;
    std::string outputFilePath;

    // Get folder path and output file path from user
    std::cout << "Please enter the folder path: ";
    std::getline(std::cin, folderPath);

    std::cout << "Please enter the output file path (e.g., output.txt): ";
    std::getline(std::cin, outputFilePath);

    // List all .dll files and write to the specified output file
    listDll(folderPath, outputFilePath);

    return 0;
}
