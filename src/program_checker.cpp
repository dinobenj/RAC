#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>


std::unordered_set<std::string> read_filename_list(const std::string& filename) {
    std::unordered_set<std::string> filenameSet;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return filenameSet;
    }

    std::string line;
    while (std::getline(file, line)) {
        filenameSet.insert(line); 
    }

    file.close();
    return filenameSet;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <csv_file> <filename_list>" << std::endl;
        return 1;
    }

    std::string csvFile = argv[1];
    std::string filenameListFile = argv[2];

    std::unordered_set<std::string> filenameSet = read_filename_list(filenameListFile);
    if (filenameSet.empty()) {
        std::cerr << "Filename list is empty or couldn't be loaded." << std::endl;
        return 1;
    }
}