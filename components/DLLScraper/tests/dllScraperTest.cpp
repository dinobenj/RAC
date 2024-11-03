// tests/dllScraperTest.cpp
#include "../include/dllScraper.h"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

int main() {
    /* TEST 1 -- stringToWString() 
     * Test description: Convert a standard string to a wide string.
     * Provided input: "TestString"
     * Expected output: L"TestString"
     */
    std::string testString = "TestString";
    std::wstring expectedWString = L"TestString";
    std::wstring convertedString = stringToWString(testString);
    if (convertedString == expectedWString) {
        std::wcout << L"[Test 1] expected output: " << expectedWString << " <==> actual output: " << convertedString << std::endl;
    } else {
        std::wcout << L"[Test 1] FAILED - expected output: " << expectedWString << " <==> actual output: " << convertedString << std::endl;
    }

    /* TEST 2 -- listDll()
     * Test description: List .dll files in a specified folder and write to an output file.
     * Setup: Create a test folder with dummy .dll files.
     * Provided input: Folder path with three dummy .dll files
     * Expected output: Output file listing exactly three .dll file names
     */
    std::string testFolderPath = "test_folder";
    std::string outputFilePath = "../output/output.txt";  // Path updated to output directory

    // Setup test environment: Create test folder and dummy .dll files
    fs::create_directory(testFolderPath);
    std::ofstream(testFolderPath + "/test1.dll").close();
    std::ofstream(testFolderPath + "/test2.dll").close();
    std::ofstream(testFolderPath + "/test3.dll").close();

    // Call listDll function to generate the output file
    listDll(testFolderPath, outputFilePath);

    // Verify output
    std::ifstream outputFile(outputFilePath);
    std::string line;
    int dllFileCount = 0;
    while (std::getline(outputFile, line)) {
        dllFileCount++;
        std::cout << "Found DLL: " << line << std::endl;
    }
    outputFile.close();

    if (dllFileCount == 3) {
        std::cout << "[Test 2] expected output: 3 DLL files <==> actual output: " << dllFileCount << " DLL files" << std::endl;
    } else {
        std::cout << "[Test 2] FAILED - expected output: 3 DLL files <==> actual output: " << dllFileCount << " DLL files" << std::endl;
    }

    // Cleanup test environment
    fs::remove_all(testFolderPath);
    fs::remove(outputFilePath);

    return EXIT_SUCCESS;
}
