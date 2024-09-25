#include <iostream>
#include <string>
#include <windows.h>

void listDll(const std::string& folderPath) {
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	std::string searchPath = folderPath + "\\.dll";

	hFind = FindirstFile(searchPath.c_str(), &fileData);

	if (hFind = INVALID_HANDLE_VALUE) {
		std::cerr << "No .dll files found or invalid folder path." << std::endl;
		return;
	}



	do {
		std::cout << fileData.cFileName << std::endl;
	} while (FindNextFile(hFind, &fileData) != 0);

	FindClose(hFind);
}


int main() {

	std::string folderPath;


	std::cout << "Please enter the file path: ";
	std::getline(std::cin, folderPath);


	listDll(folderPath);

	return 0;

}#include <iostream>
#include <string>
#include <windows.h>

void listDll(const std::string& folderPath) {
	WIN32_FIND_DATA fileData;
	HANDLE hFind;

	std::string searchPath = folderPath + "\\.dll";

	hFind = FindirstFile(searchPath.c_str(), &fileData);

	if (hFind = INVALID_HANDLE_VALUE) {
		std::cerr << "No .dll files found or invalid folder path." << std::endl;
		return;
	}



	do {
		std::cout << fileData.cFileName << std::endl;
	} while (FindNextFile(hFind, &fileData) != 0);

	FindClose(hFind);
}


int main() {

	std::string folderPath;


	std::cout << "Please enter the file path: ";
	std::getline(std::cin, folderPath);


	listDll(folderPath);

	return 0;

}