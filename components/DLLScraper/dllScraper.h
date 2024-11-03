// dllScraper.h
#ifndef DLL_LISTER_H
#define DLL_LISTER_H

#include <string>

// Function to list all .dll files in a specified folder and output the list to a specified file
void listDll(const std::string& folderPath, const std::string& outputFilePath);

#endif // DLL_LISTER_H
